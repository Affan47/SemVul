make_verb(void)
{


    int Inform_verb, meta_verb_flag=FALSE, verb_equals_form=FALSE;

    char *English_verbs_given[32]; int no_given = 0, i;

    directive_keywords.enabled = TRUE;

    get_next_token();

    if ((token_type == DIR_KEYWORD_TT) && (token_value == META_DK))
    {   meta_verb_flag = TRUE;
        get_next_token();
    }

    while ((token_type == DQ_TT) || (token_type == SQ_TT))
    {   English_verbs_given[no_given++] = token_text;
        get_next_token();
    }

    if (no_given == 0)
    {   ebf_error("English verb in quotes", token_text);
        panic_mode_error_recovery(); return;
    }

    if ((token_type == SEP_TT) && (token_value == SETEQUALS_SEP))
    {   verb_equals_form = TRUE;
        get_next_token();
        Inform_verb = get_verb();
        if (Inform_verb == -1) return;
        get_next_token();
        if (!((token_type == SEP_TT) && (token_value == SEMICOLON_SEP)))
            ebf_error("';' after English verb", token_text);
    }
    else
    {   Inform_verb = no_Inform_verbs;
        if (no_Inform_verbs == MAX_VERBS)
            memoryerror("MAX_VERBS",MAX_VERBS);
    }

    for (i=0; i<no_given; i++)
    {   dictionary_add(English_verbs_given[i],
            0x41 + ((meta_verb_flag)?0x02:0x00),
            0xff-Inform_verb, 0);
        register_verb(English_verbs_given[i], Inform_verb);
    }

    if (!verb_equals_form)
    {   int lines = 0;
        put_token_back();
        while (grammar_line(no_Inform_verbs, lines++)) ;
        Inform_verbs[no_Inform_verbs++].lines = --lines;
    }

    directive_keywords.enabled = FALSE;
}
