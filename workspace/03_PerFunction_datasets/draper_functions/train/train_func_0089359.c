WordHood_Alphabet_create_from_CodonSubmat(
                    CodonSubmat *cs, gboolean case_sensitive_input){
    register gint a, b, c;
    register gchar *input_alphabet = "ABCDGHKMNRSTVWY",
                   *output_alphabet = "ACGT";
    register WordHood_Alphabet *wha = WordHood_Alphabet_create(3,
            input_alphabet, output_alphabet, case_sensitive_input);
    wha->submat = NULL;
    wha->codon_submat = CodonSubmat_share(cs);
    for(a = 0; a < 4; a++)
        for(b = 0; b < 4; b++)
            for(c = 0; c < 4; c++)
                g_ptr_array_add(wha->member_list,
                        g_strdup_printf("%c%c%c", output_alphabet[a],
                                                  output_alphabet[b],
                                                  output_alphabet[c]));
    wha->score_func = WordHood_CodonSubmat_score_func;
    wha->is_valid_func = WordHood_CodonSubmat_is_valid_func;
    wha->index_func = WordHood_CodonSubmat_index_func;
    return wha;
    }
