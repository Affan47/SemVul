Parse (const char *iSource, size_t iLength, size_t &oLength)
{
    Token retval = Parse (Token (Token::TK_TEXT, iSource, iLength));
    if (retval.Type == Token::TK_ERROR)
        return NULL;

    oLength = retval.Length;
    retval.Allocated = 0;
    return retval.Buffer;
}
