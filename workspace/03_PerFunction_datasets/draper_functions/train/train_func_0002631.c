json_loadf(FILE *input, size_t flags, json_error_t *error)
{
    lex_t lex;
    const char *source;
    json_t *result;
    (void)flags;

    if(lex_init(&lex, (get_func)fgetc, (eof_func)feof, input))
        return NULL;

    if(input == stdin)
        source = "<stdin>";
    else
        source = "<stream>";

    jsonp_error_init(error, source);

    result = parse_json(&lex, error);
    if(!result)
        goto out;

    lex_scan(&lex, error);
    if(lex.token != TOKEN_EOF) {
        error_set(error, &lex, "end of file expected");
        json_decref(result);
        result = NULL;
    }

out:
    lex_close(&lex);
    return result;
}
