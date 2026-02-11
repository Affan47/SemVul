path_set_fv_mask_from_term_list(Path *p)
{
    List *l;
    fv_kind fv;

    for (fv = FULL; fv <= LAST_FV; fv++) {
        p->fv_mask[fv] = FALSE;
    }
    for (l = p->term_list; l != NULL; l = l->next) {
        Term *term = list_first_data(l);
        for (fv = FULL; fv <= LAST_FV; fv++) {
            if (term->fv_mask[fv]) {
                p->fv_mask[fv] = TRUE;
            }
        }
    }
}
