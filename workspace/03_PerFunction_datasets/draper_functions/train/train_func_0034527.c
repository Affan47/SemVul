ll_print(FILE *stream, char *format, linked_list_t *list)
{
    format_details_t *details = calloc(1, sizeof(format_details_t));
    char *next = format;
    char *list_text = NULL;

    ll_rewind(list);

    while(*next != '\0') {
        format_handler(&next, details);
        if (details->error_char == -1) {
            if (details->plain_output > -1) {
                fputc(details->plain_output, stream);
            } else {
                list_text = ll_next(list);

                if (list_text != NULL) {
                    fprintf(stream, details->format_substring, list_text);
                }
            }
        }
    }
    fputc('\n', stream);
    free(details);
}
