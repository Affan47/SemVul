generate_reports (struct prog_ctx *ctx)
{
    ListIterator   i;
    struct report *r;

    if (!ctx->reports)
        log_fatal (1, "No reports requested!");

    i = list_iterator_create (ctx->reports);
    while ((r = list_next (i))) {
        if (r->report != NULL)
            r->report (ctx);
    }
    list_iterator_destroy (i);
    return;
}
