peekToken(uint32_t lookaheadCount, struct UString **tokenValue, uint32_t *linenumber, struct UString *comment, UErrorCode *status)
{
    uint32_t i = (lookaheadPosition + lookaheadCount) % (MAX_LOOKAHEAD + 1);

    if (U_FAILURE(*status))
    {
        return TOK_ERROR;
    }

    if (lookaheadCount >= MAX_LOOKAHEAD)
    {
        *status = U_INTERNAL_PROGRAM_ERROR;
        return TOK_ERROR;
    }

    if (tokenValue != NULL)
    {
        *tokenValue = &lookahead[i].value;
    }

    if (linenumber != NULL)
    {
        *linenumber = lookahead[i].line;
    }

    if(comment != NULL){
        ustr_cpy(comment, &(lookahead[lookaheadPosition].comment), status);
    }

    return lookahead[i].type;
}
