check_context_ids(BreakpointInfo * bp, Context * ctx, int location) {
    if (bp->context_ids != NULL) {
        int ok = 0;
        char ** ids = bp->context_ids;
        while (!ok && *ids != NULL) {
            Context * c = id2ctx(*ids++);
            if (c == NULL) continue;
            ok = location ? c->mem == ctx->mem : c == ctx || c == ctx->parent;
        }
        return ok;
    }
    return 1;
}
