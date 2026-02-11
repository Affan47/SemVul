rsvg_xinclude_handler_end (RsvgSaxHandler * self, const char *name)
{
    RsvgSaxHandlerXinclude *z = (RsvgSaxHandlerXinclude *) self;
    RsvgHandle *ctx = z->ctx;

    if (!strcmp (name, "include") || !strcmp (name, "xi:include")) {
        if (ctx->priv->handler != NULL) {
            RsvgSaxHandler *previous_handler;

            previous_handler = z->prev_handler;
            ctx->priv->handler->free (ctx->priv->handler);
            ctx->priv->handler = previous_handler;
        }
    } else if (z->in_fallback) {
        if (!strcmp (name, "xi:fallback"))
            z->in_fallback = FALSE;
    }
}
