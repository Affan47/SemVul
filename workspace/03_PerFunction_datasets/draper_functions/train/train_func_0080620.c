worker_count_context_uri_tokens(const char * context)
{
    const char * c = context;
    int count = 0;
    while (c && *c) {
        if ('/' == *c++)
            count++;
    }
    return count;
}
