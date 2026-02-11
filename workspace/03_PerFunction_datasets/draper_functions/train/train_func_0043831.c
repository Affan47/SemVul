read_number_or_peculiar(ScmObj port)
{
    scm_ichar_t c;
    int err;
    size_t len;
    char buf[INT_LITERAL_LEN_MAX + sizeof("")];
    DECLARE_INTERNAL_FUNCTION("read");

    CDBG((SCM_DBG_PARSER, "read"));

    c = scm_port_peek_char(port);
    SCM_ASSERT(ICHAR_ASCII_CLASS(c)
               & (SCM_CH_DIGIT | SCM_CH_PECULIAR_IDENTIFIER_CAND));

#if SCM_USE_NUMBER
    if (ICHAR_NUMERICP(c))
        return read_number(port, 'd');

    if (c == '+' || c == '-') {
        len = read_token(port, &err, buf, sizeof(buf), SCM_CH_DELIMITER);
        if (err == TOKEN_BUF_EXCEEDED)
            ERR("invalid number literal");


        if (!buf[1])
            return scm_intern(buf);

        return parse_number(port, buf, sizeof(buf), 'd');
    }
#endif

    if (c == '.') {
        read_token(port, &err, buf, sizeof(buf), SCM_CH_DELIMITER);
        if (strcmp(buf, "...") == 0)
            return SYM_ELLIPSIS;


        ERR("invalid identifier: ~S", buf);
    }

    if (c == '@')
        ERR("invalid identifier starting with @");

    return read_symbol(port);
}
