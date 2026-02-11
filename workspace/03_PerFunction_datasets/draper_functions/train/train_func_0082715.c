AlignmentView_add_FRAMESHIFT(AlignmentView *av,
                gint advance_query, gint advance_target,
                gint total_length, Sequence *query, Sequence *target,
                gint query_pos, gint target_pos, Translate *translate){
    register gint i, j;
    register gint curr_query_pos = query_pos,
                  curr_target_pos = target_pos;
    static gchar seq_string[4], match_string[4], gap_string[4];
    register Alphabet_Type emitted_alphabet_type;
    g_assert(!(advance_query && advance_target));
    match_string[0] = '#';
    gap_string[0] = '-';
    if(advance_query)
        emitted_alphabet_type = query->alphabet->type;
    else
        emitted_alphabet_type = target->alphabet->type;
    for(i = 0; i < total_length; i++){
        for(j = 0; j < (advance_query|advance_target); j++){
            if(advance_query)
                seq_string[j] = Sequence_get_symbol(query, curr_query_pos+j);
            else
                seq_string[j] = Sequence_get_symbol(target, curr_target_pos+j);
            match_string[j] = match_string[0];
            gap_string[j] = gap_string[0];
            }
        seq_string[j] = match_string[j] = gap_string[j] = '\0';
        if(emitted_alphabet_type == Alphabet_Type_PROTEIN){
            strncpy(seq_string, Alphabet_aa2tla(seq_string[0]), 3);
            match_string[2] = match_string[1] = match_string[0];
            gap_string[2] = gap_string[1] = gap_string[0];
            seq_string[3] = match_string[3] = gap_string[3] = '\0';
            }
        if(advance_query)
            AlignmentView_add(av, seq_string,
                                  match_string,
                                  match_string,
                                  gap_string,
                                  gap_string,
                                  curr_query_pos, curr_target_pos);
        else
            AlignmentView_add(av, gap_string,
                                  gap_string,
                                  match_string,
                                  match_string,
                                  seq_string,
                                  curr_query_pos, curr_target_pos);
        curr_query_pos += advance_query;
        curr_target_pos += advance_target;
        }
    return;
    }
