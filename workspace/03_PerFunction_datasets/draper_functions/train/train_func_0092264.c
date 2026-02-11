get_verb(void)
{


    int j;

    if ((token_type == DQ_TT) || (token_type == SQ_TT))
    {   j = find_or_renumber_verb(token_text, NULL);
        if (j==-1)
            error_named("There is no previous grammar for the verb",
                token_text);
        return j;
    }

    ebf_error("an English verb in quotes", token_text);

    return -1;
}
