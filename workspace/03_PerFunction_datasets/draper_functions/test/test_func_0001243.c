step_root(struct step *step, struct tree *ctx,
                              struct tree *root_ctx) {
    struct tree *node = NULL;
    switch (step->axis) {
    case SELF:
    case CHILD:
    case DESCENDANT:
    case PARENT:
    case ANCESTOR:
    case PRECEDING_SIBLING:
    case FOLLOWING_SIBLING:

        if (ctx == ctx->parent && root_ctx != NULL)
            node = root_ctx;
        else
            node = ctx;
        break;
    case ROOT:
    case DESCENDANT_OR_SELF:
        node = ctx;
        break;
    default:
        assert(0);
    }
    if (node == NULL)
        return NULL;
    return node;
}
