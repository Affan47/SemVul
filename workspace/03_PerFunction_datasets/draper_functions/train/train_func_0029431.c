SetSpanDepTarget(JSContext *cx, JSCodeGenerator *cg, JSSpanDep *sd,
                 ptrdiff_t off)
{
    AddJumpTargetArgs args;

    if (off < JUMPX_OFFSET_MIN || JUMPX_OFFSET_MAX < off) {
        ReportStatementTooLarge(cx, cg);
        return JS_FALSE;
    }

    args.cx = cx;
    args.cg = cg;
    args.offset = sd->top + off;
    args.node = NULL;
    AddJumpTarget(&args, &cg->jumpTargets);
    if (!args.node)
        return JS_FALSE;

#ifdef DEBUG_brendan
    AVLCheck(cg->jumpTargets);
#endif

    SD_SET_TARGET(sd, args.node);
    return JS_TRUE;
}
