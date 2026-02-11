Match_3_3_split_display_func(Match *match,
                              Sequence *query, Sequence *target,
                              guint qp1, guint qp2, guint qp3,
                              guint tp1, guint tp2, guint tp3,
                              gchar *display_str){
    register gchar query_symbol, target_symbol, display_symbol;
    query_symbol = Translate_base(match->mas->translate,
                       Sequence_get_symbol(query, qp1),
                       Sequence_get_symbol(query, qp2),
                       Sequence_get_symbol(query, qp3));
    target_symbol = Translate_base(match->mas->translate,
                       Sequence_get_symbol(target, tp1),
                       Sequence_get_symbol(target, tp2),
                       Sequence_get_symbol(target, tp3));
    display_symbol = Match_get_display_symbol(
                           match->mas->protein_submat,
                           query_symbol, target_symbol);

    display_str[0] = display_symbol;
    if(query_symbol == target_symbol){
        if(toupper(Sequence_get_symbol(query, qp1))
        != toupper(Sequence_get_symbol(target, tp1)))
            display_str[0] = '+';
    } else {
        if(toupper(Sequence_get_symbol(query, qp1))
        == toupper(Sequence_get_symbol(target, tp1)))
            display_str[0] = '!';
        }

    display_str[1] = display_symbol;
    if(query_symbol == target_symbol){
        if(toupper(Sequence_get_symbol(query, qp2))
        != toupper(Sequence_get_symbol(target, tp2)))
            display_str[1] = '+';
    } else {
        if(toupper(Sequence_get_symbol(query, qp2))
        == toupper(Sequence_get_symbol(target, tp2)))
            display_str[1] = '!';
        }

    display_str[2] = display_symbol;
    if(query_symbol == target_symbol){
        if(toupper(Sequence_get_symbol(query, qp3))
        != toupper(Sequence_get_symbol(target, tp3)))
            display_str[2] = '+';
    } else {
        if(toupper(Sequence_get_symbol(query, qp3))
        == toupper(Sequence_get_symbol(target, tp3)))
            display_str[2] = '!';
        }

    display_str[3] = '\0';
    return;
    }
