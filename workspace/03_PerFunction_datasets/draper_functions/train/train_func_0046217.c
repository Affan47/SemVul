error_set(json_error_t *error, const lex_t *lex,
                      const char *msg, ...)
{
    va_list ap;
    char msg_text[JSON_ERROR_TEXT_LENGTH];

    int line = -1, col = -1;
    const char *result = msg_text;

    if(!error)
        return;

    va_start(ap, msg);
    vsnprintf(msg_text, JSON_ERROR_TEXT_LENGTH, msg, ap);
    va_end(ap);

    if(lex)
    {
        const char *saved_text = strbuffer_value(&lex->saved_text);
        char msg_with_context[JSON_ERROR_TEXT_LENGTH];

        line = lex->line;

        if(saved_text && saved_text[0])
        {
            if(lex->saved_text.length <= 20) {
                snprintf(msg_with_context, JSON_ERROR_TEXT_LENGTH,
                         "%s near '%s'", msg_text, saved_text);
                result = msg_with_context;
            }
        }
        else
        {
            snprintf(msg_with_context, JSON_ERROR_TEXT_LENGTH,
                     "%s near end of file", msg_text);
            result = msg_with_context;
        }
    }

    jsonp_error_set(error, line, col, "%s", result);
}
