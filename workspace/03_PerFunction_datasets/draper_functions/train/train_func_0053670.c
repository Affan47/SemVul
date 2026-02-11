reflect_phase_info_to_block_and_max_term(List *phase_info_list)
{
    List *li;

    for (li = phase_info_list; li != NULL; li = li->next) {
        Phase_info *p = list_first_data(li);

        if (phase_info_get_kind(p) == SINGLE) {
            Block_info *b = phase_info_get_body_b(p);

            if (block_info_get_kind(b) != EMT) {
                block_info_set_margin(b, phase_info_get_margin(p));
                block_info_set_fv(b, phase_info_get_fv(p));
            }

        } else if (phase_info_get_kind(p) == MAX) {
            List *li;
            real margin, upper;
            real length[FV_STATE_NUM];

            Max_term *m = phase_info_get_body_m(p);
            List *path_list = max_term_get_path_list(m);

            margin = phase_info_get_margin(p);
            set_length_of_max_term_with_margin(m, length, TRUE);
            upper = margin + length[FULL];

            max_term_set_margin(m, upper - max_term_get_sche_length(m, FULL));
            max_term_set_fv(m, phase_info_get_fv(p));

            for (li = path_list; li != NULL; li = li->next) {
                Path *pt = list_first_data(li);

                path_set_margin(pt, upper - path_get_sche_length(pt, FULL));
                path_set_fv(pt, phase_info_get_fv(p));
            }

        } else {
            Clump_term *c = phase_info_get_body_c(p);
            List *list = clump_term_get_block_info_list(c);
            fv_kind fv = phase_info_get_fv(p);

            set_margin_and_fv_for_block_info_list(list, fv, FALSE, FALSE);
        }
    }
}
