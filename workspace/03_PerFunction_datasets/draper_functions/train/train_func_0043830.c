handle_content(struct ntb_mail_parser *parser,
               const uint8_t *data,
               size_t length,
               struct ntb_error **error)
{
        switch (parser->encoding) {
        case NTB_MAIL_PARSER_ENCODING_BASE64:
                return handle_content_base64(parser, data, length, error);

        case NTB_MAIL_PARSER_ENCODING_QUOTED_PRINTABLE:
                return handle_content_quoted_printable(parser,
                                                       data,
                                                       length,
                                                       error);

        case NTB_MAIL_PARSER_ENCODING_RAW:
                return handle_content_raw(parser, data, length, error);
        }

        assert(false);

        return -1;
}
