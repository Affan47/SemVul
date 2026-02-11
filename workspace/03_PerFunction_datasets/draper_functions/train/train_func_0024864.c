unpack_warning_value(ParseContext *context)
{
    Octstr *decoded = NULL;
    Octstr *warn_code = NULL;
    Octstr *warn_agent = NULL;
    Octstr *warn_text = NULL;
    unsigned char quote = '"';

    warn_code = wsp_unpack_integer_value(context);

    warn_agent = parse_get_nul_string(context);
    if (warn_agent && octstr_get_char(warn_agent, 0) == WSP_QUOTE)
        octstr_delete(warn_agent, 0, 1);

    warn_text = parse_get_nul_string(context);
    if (warn_text && octstr_get_char(warn_text, 0) == WSP_QUOTE)
        octstr_delete(warn_text, 0, 1);
    if (octstr_get_char(warn_text, 0) != quote)
        octstr_insert_data(warn_text, 0, (char *)&quote, 1);
    if (octstr_get_char(warn_text, octstr_len(warn_text) - 1) != quote)
        octstr_append_char(warn_text, quote);

    if (parse_error(context) || !warn_agent || !warn_text)
        goto error;

    decoded = octstr_create("");
    octstr_append(decoded, warn_code);
    octstr_append_char(decoded, ' ');
    octstr_append(decoded, warn_agent);
    octstr_append_char(decoded, ' ');
    octstr_append(decoded, warn_text);

    octstr_destroy(warn_agent);
    octstr_destroy(warn_code);
    octstr_destroy(warn_text);
    return decoded;

error:
    warning(0, "Bad format for warning-value.");
    octstr_destroy(warn_agent);
    octstr_destroy(warn_code);
    octstr_destroy(warn_text);
    octstr_destroy(decoded);
    return NULL;
}
