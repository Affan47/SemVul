realParseTable(ParseState* state, struct SResource *table, char *tag, uint32_t startline, UErrorCode *status)
{
    struct SResource  *member = NULL;
    struct UString    *tokenValue=NULL;
    struct UString    comment;
    enum   ETokenType token;
    char              subtag[1024];
    uint32_t          line;
    UBool             readToken = FALSE;


    if(isVerbose()){
        printf(" parsing table %s at line %i \n", (tag == NULL) ? "(null)" : tag, (int)startline);
    }
    for (;;)
    {
        ustr_init(&comment);
        token = getToken(state, &tokenValue, &comment, &line, status);

        if (token == TOK_CLOSE_BRACE)
        {
            if (!readToken) {
                warning(startline, "Encountered empty table");
            }
            return table;
        }

        if (token != TOK_STRING)
        {
            *status = U_INVALID_FORMAT_ERROR;

            if (token == TOK_EOF)
            {
                error(startline, "unterminated table");
            }
            else
            {
                error(line, "unexpected token %s", tokenNames[token]);
            }

            return NULL;
        }

        if(uprv_isInvariantUString(tokenValue->fChars, -1)) {
            u_UCharsToChars(tokenValue->fChars, subtag, u_strlen(tokenValue->fChars) + 1);
        } else {
            *status = U_INVALID_FORMAT_ERROR;
            error(line, "invariant characters required for table keys");
            return NULL;
        }

        if (U_FAILURE(*status))
        {
            error(line, "parse error. Stopped parsing tokens with %s", u_errorName(*status));
            return NULL;
        }

        member = parseResource(state, subtag, &comment, status);

        if (member == NULL || U_FAILURE(*status))
        {
            error(line, "parse error. Stopped parsing resource with %s", u_errorName(*status));
            return NULL;
        }

        table_add(table, member, line, status);

        if (U_FAILURE(*status))
        {
            error(line, "parse error. Stopped parsing table with %s", u_errorName(*status));
            return NULL;
        }
        readToken = TRUE;
        ustr_deinit(&comment);
   }


}
