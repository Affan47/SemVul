parse_get_nul_string(ParseContext *context)
{
    Octstr *result;
    long pos;

    gw_assert(context != NULL);

    pos = octstr_search_char(context->data, 0, context->pos);
    if (pos < 0 || pos >= context->limit) {
        context->error = 1;
        return NULL;
    }

    result = octstr_copy(context->data, context->pos, pos - context->pos);
    context->pos = pos + 1;

    return result;
}
