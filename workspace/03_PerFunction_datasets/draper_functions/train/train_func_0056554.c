process_error()
{
    switch (m_parser.error()) {
        case Parser::PARSE_BODY_TOO_LARGE:
            m_reply.set_status(413, "Request entity too large");
            break;

        case Parser::PARSE_URI_TOO_LONG:
            m_reply.set_status(414, "Request URI too long");
            break;

        default:
            m_reply.set_status(400, "Bad request");
            break;
    }
}
