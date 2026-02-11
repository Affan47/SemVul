js_SetJumpOffset(JSContext *cx, JSCodeGenerator *cg, jsbytecode *pc,
                 ptrdiff_t off)
{
    if (!cg->spanDeps) {
        if (JUMP_OFFSET_MIN <= off && off <= JUMP_OFFSET_MAX) {
            SET_JUMP_OFFSET(pc, off);
            return JS_TRUE;
        }

        if (!BuildSpanDepTable(cx, cg))
            return JS_FALSE;
    }

    return SetSpanDepTarget(cx, cg, GetSpanDep(cg, pc), off);
}
