blogc_error_print(blogc_error_t *err)
{
    if (err == NULL)
        return;

    switch(err->type) {
        case BLOGC_ERROR_SOURCE_PARSER:
            fprintf(stderr, "blogc: error: source: %s\n", err->msg);
            break;
        case BLOGC_ERROR_TEMPLATE_PARSER:
            fprintf(stderr, "blogc: error: template: %s\n", err->msg);
            break;
        case BLOGC_ERROR_LOADER:
            fprintf(stderr, "blogc: error: loader: %s\n", err->msg);
            break;
        case BLOGC_WARNING_DATETIME_PARSER:
            fprintf(stderr, "blogc: warning: datetime: %s\n", err->msg);
            break;
        case BLOGC_WARNING_CONTENT_PARSER:
            fprintf(stderr, "blogc: warning: content: %s\n", err->msg);
            break;
        default:
            fprintf(stderr, "blogc: error: %s\n", err->msg);
    }
}
