EmitDestructuringLHS(JSContext *cx, JSCodeGenerator *cg, JSParseNode *pn)
{
    jsuint slot;


    if (pn->pn_type == TOK_RB || pn->pn_type == TOK_RC) {
        if (!EmitDestructuringOpsHelper(cx, cg, pn))
            return JS_FALSE;
        if (js_Emit1(cx, cg, JSOP_POP) < 0)
            return JS_FALSE;
    } else {
        if (pn->pn_type == TOK_NAME) {
            if (!BindNameToSlot(cx, cg, pn))
                return JS_FALSE;
            if (pn->isConst() && !pn->isInitialized())
                return js_Emit1(cx, cg, JSOP_POP) >= 0;
        }

        switch (pn->pn_op) {
          case JSOP_SETNAME:


            if (!EmitElemOp(cx, pn, JSOP_ENUMELEM, cg))
                return JS_FALSE;
            break;

          case JSOP_SETCONST:
            if (!EmitElemOp(cx, pn, JSOP_ENUMCONSTELEM, cg))
                return JS_FALSE;
            break;

          case JSOP_SETLOCAL:
            slot = (jsuint) pn->pn_cookie;
            EMIT_UINT16_IMM_OP(JSOP_SETLOCALPOP, slot);
            break;

          case JSOP_SETARG:
          case JSOP_SETGVAR:
            slot = (jsuint) pn->pn_cookie;
            EMIT_UINT16_IMM_OP(PN_OP(pn), slot);
            if (js_Emit1(cx, cg, JSOP_POP) < 0)
                return JS_FALSE;
            break;

          default:
#if JS_HAS_LVALUE_RETURN || JS_HAS_XML_SUPPORT
          {
            ptrdiff_t top;

            top = CG_OFFSET(cg);
            if (!js_EmitTree(cx, cg, pn))
                return JS_FALSE;
            if (js_NewSrcNote2(cx, cg, SRC_PCBASE, CG_OFFSET(cg) - top) < 0)
                return JS_FALSE;
            if (js_Emit1(cx, cg, JSOP_ENUMELEM) < 0)
                return JS_FALSE;
            break;
          }
#endif
          case JSOP_ENUMELEM:
            JS_ASSERT(0);
        }
    }

    return JS_TRUE;
}
