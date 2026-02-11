parseArray(ParseState* state, char *tag, uint32_t startline, const struct UString *comment, UErrorCode *status)
{
    struct SResource  *result = NULL;
    struct SResource  *member = NULL;
    struct UString    *tokenValue;
    struct UString    memberComments;
    enum   ETokenType token;
    UBool             readToken = FALSE;

    result = array_open(state->bundle, tag, comment, status);

    if (result == NULL || U_FAILURE(*status))
    {
        return NULL;
    }
    if(isVerbose()){
        printf(" array %s at line %i \n",  (tag == NULL) ? "(null)" : tag, (int)startline);
    }

    ustr_init(&memberComments);


    for (;;)
    {

        ustr_setlen(&memberComments, 0, status);


        token = peekToken(state, 0, &tokenValue, NULL, &memberComments, status);


        if (token == TOK_CLOSE_BRACE)
        {
            getToken(state, NULL, NULL, NULL, status);
            if (!readToken) {
                warning(startline, "Encountered empty array");
            }
            break;
        }

        if (token == TOK_EOF)
        {
            res_close(result);
            *status = U_INVALID_FORMAT_ERROR;
            error(startline, "unterminated array");
            return NULL;
        }


        if (token == TOK_STRING)
        {
            getToken(state, &tokenValue, &memberComments, NULL, status);
            member = string_open(state->bundle, NULL, tokenValue->fChars, tokenValue->fLength, &memberComments, status);
        }
        else
        {
            member = parseResource(state, NULL, &memberComments, status);
        }

        if (member == NULL || U_FAILURE(*status))
        {
            res_close(result);
            return NULL;
        }

        array_add(result, member, status);

        if (U_FAILURE(*status))
        {
            res_close(result);
            return NULL;
        }


        token = peekToken(state, 0, NULL, NULL, NULL, status);

        if (token == TOK_COMMA)
        {
            getToken(state, NULL, NULL, NULL, status);
        }

        if (U_FAILURE(*status))
        {
            res_close(result);
            return NULL;
        }
        readToken = TRUE;
    }

    ustr_deinit(&memberComments);
    return result;
}
