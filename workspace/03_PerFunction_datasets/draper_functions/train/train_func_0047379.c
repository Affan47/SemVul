test_cr_parser_parse (guchar * a_file_uri)
{
        enum CRStatus status = CR_OK;
        CROMParser *parser = NULL;
        CRStyleSheet *stylesheet = NULL;

        g_return_val_if_fail (a_file_uri, CR_BAD_PARAM_ERROR);

        parser = cr_om_parser_new (NULL);
        status = cr_om_parser_parse_file (parser, a_file_uri, CR_ASCII,
                                          &stylesheet);
        if (status == CR_OK && stylesheet) {
                cr_stylesheet_dump (stylesheet, stdout);
                cr_stylesheet_destroy (stylesheet);
        }
        cr_om_parser_destroy (parser);

        return status;
}
