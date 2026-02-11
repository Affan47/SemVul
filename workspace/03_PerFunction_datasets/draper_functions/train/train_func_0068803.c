parse_context_destroy(ParseContext *context)
{
    gw_assert(context != NULL);

    if (context->limit_stack) {
        while (gwlist_len(context->limit_stack) > 0)
            gw_free(gwlist_extract_first(context->limit_stack));
        gwlist_destroy(context->limit_stack, NULL);
    }
    gw_free(context);
}
