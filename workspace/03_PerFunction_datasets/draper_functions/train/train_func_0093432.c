libcurl_gmarkup_glue(void *ptr, size_t size1, size_t size2,
                                   void *stream) {
    GMarkupParseContext *context = stream;


    size_t read_size = size1 * size2;
    GError * error = NULL;

    read_size = size1 * size2;

    if (g_markup_parse_context_parse(context, ptr, read_size, &error)) {
        return read_size;
    } else {
        if (error == NULL) {
            g_fprintf(stderr, "Internal error parsing XML.\n");
        } else {
            g_fprintf(stderr, "Error parsing XML: %s\n",
                    error->message);
            g_error_free(error);
        }
        exit(EXIT_FAILURE);
    }
}
