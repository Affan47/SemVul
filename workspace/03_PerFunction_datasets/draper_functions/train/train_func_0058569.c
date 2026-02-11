show_edit_replace(ADT_SEARCH *ptr_adt_search,
                                         ADT_EDIT *ptr_adt_edit)

{
    char    *seq_anfang, *seq_loop_start, *seq_loop_ptr;
    char    *matchp_anfang;
    char    *replace_anfang, *replace_loop_ptr;
    AD_ERR  *ad_err;

    matchp_anfang                   =  ptr_adt_search->matchpattern;
    replace_anfang                  =  ptr_adt_search->replace_string;
    seq_anfang                      =  ptr_adt_search->seq_anfang;

    ptr_adt_search->string_replace = 0;
    long    var_start_cursor_pos    =
        ptr_adt_search->replace_start_cursor_pos;

    seq_loop_start = seq_anfang + var_start_cursor_pos;
    seq_loop_ptr   = seq_loop_start;


    long    match_len       = strlen(ptr_adt_search->matchpattern);
    long    replace_len     = strlen(ptr_adt_search->replace_string);

    if( (match_len == replace_len)  ||
        (ptr_adt_search->gaps == 0) || (ptr_adt_search->gaps == 1) ) {


        seq_loop_ptr = seq_loop_start;
        for( replace_loop_ptr = replace_anfang ;
             *replace_loop_ptr != '\0' ; replace_loop_ptr++ ) {
            *seq_loop_ptr = *replace_loop_ptr;
            seq_loop_ptr++;
        }
    }

    else {

        ad_err = remove( strlen(matchp_anfang),
                         (int)var_start_cursor_pos,1  );
        if (ad_err) {
            replace(ptr_adt_search->save_sequence,0,1);

            free(ptr_adt_search->save_sequence);
            return ad_err;
        }


        else if( strlen(replace_anfang) != 0 ){
            ad_err = insert( replace_anfang,
                             (int)var_start_cursor_pos ,1 );

            if (ad_err) {
                replace(ptr_adt_search->save_sequence,0,1);

                free(ptr_adt_search->save_sequence);
                return ad_err;
            }
            ptr_adt_search->seq_anfang = get();
        }
    }


    ptr_adt_edit->actual_cursorpos_editor =
        ptr_adt_search->replace_start_cursor_pos +
        strlen(replace_anfang) - 1;


    ptr_adt_search->string_replace = 1;
    return 0;

}
