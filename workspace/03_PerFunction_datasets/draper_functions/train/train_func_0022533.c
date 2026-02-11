make_lexical_interface_tables(void)
{   int i;
    for (i=0;i<103;i++)
        separators_to_operators[i] = NOT_AN_OPERATOR;
    for (i=0;i<NUM_OPERATORS;i++)
        if (operators[i].token_type == SEP_TT)
            separators_to_operators[operators[i].token_value] = i;

    for (i=0;i<7;i++)
        conditionals_to_operators[i] = NOT_AN_OPERATOR;
    for (i=0;i<NUM_OPERATORS;i++)
        if (operators[i].token_type == CND_TT)
            conditionals_to_operators[operators[i].token_value] = i;

    for (i=0;i<301;i++) token_type_allowable[i] = 0;

    token_type_allowable[VARIABLE_TT] = 1;
    token_type_allowable[SYSFUN_TT] = 1;
    token_type_allowable[DQ_TT] = 1;
    token_type_allowable[DICTWORD_TT] = 1;
    token_type_allowable[SUBOPEN_TT] = 1;
    token_type_allowable[SUBCLOSE_TT] = 1;
    token_type_allowable[SMALL_NUMBER_TT] = 1;
    token_type_allowable[LARGE_NUMBER_TT] = 1;
    token_type_allowable[ACTION_TT] = 1;
    token_type_allowable[SYSTEM_CONSTANT_TT] = 1;
    token_type_allowable[OP_TT] = 1;
}
