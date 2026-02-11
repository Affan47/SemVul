local_array_lu_set_for_dlg_sb(Block *head)
{
    Block *b;
    Boolean shrink = FALSE;

    for (b = head; b != NULL; b = b->next) {
        if (b->dlg_sb_flg
            && b->kind == SB
            && (b->lm_assigned_flg
                || b->cmp_localize != NULL)) {
            replace_array_real_lu(b);
            shrink = TRUE;
        }
    }

    if (shrink) {
        shrink_argument_table_for_cmp(head->outer);
    }
}
