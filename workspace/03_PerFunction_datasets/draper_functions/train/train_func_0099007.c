opal_show_vhelp_internal(const char *filename, const char *topic,
                                    bool want_error_header, va_list arglist)
{
    char *output;


    output = opal_show_help_vstring(filename, topic, want_error_header,
                                    arglist);


    if (NULL != output) {
        opal_output(output_stream, "%s", output);
        free(output);
    }

    return (NULL == output) ? OPAL_ERROR : OPAL_SUCCESS;
}
