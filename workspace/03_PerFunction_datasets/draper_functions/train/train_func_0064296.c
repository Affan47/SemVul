rsvg_node_draw (RsvgNode * self, RsvgDrawingCtx * ctx, int dominate)
{
    RsvgState *state;
    GSList *stacksave;

    state = self->state;

    stacksave = ctx->drawsub_stack;
    if (stacksave) {
        if (stacksave->data != self)
            return;
        ctx->drawsub_stack = stacksave->next;
    }
    if (!state->visible)
        return;

    if (g_slist_find(ctx->ptrs, self) != NULL)
    {


        g_warning("Circular SVG reference noticed, dropping");
        return;
    }
    ctx->ptrs = g_slist_append(ctx->ptrs, self);

    self->draw (self, ctx, dominate);
    ctx->drawsub_stack = stacksave;

    ctx->ptrs = g_slist_remove(ctx->ptrs, self);
}
