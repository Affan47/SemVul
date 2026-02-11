dir_move_forward_beyond_label(Directive *dir)
{
    Statement *stm;
    Directive *dir_list, *dpt;
    Directive *ret = NULL;
    Boolean   rep = TRUE;

    if (dir->owners_type == DIR_OWNERIS_STATEMENT) {

        while (rep) {
            stm = dir->owner.statement;

            for (dir_list = dir ; dir_list->prev ; dir_list = dir_list->prev)
            ;
            if (dir_list == stm->dir_pre_head && stm->prev != NULL) {
                stm->dir_pre_head = dir->next;
                if (dir->next != NULL) {
                    dir->next->prev = NULL;
                    dir->next = NULL;
                }
                stm = stm->prev;
                for (dpt = dir_list ; dpt!=dir->next ; dpt = dpt->next) {
                    dpt->owner.statement = stm;
                }
                stm->dir_post_head = dir_link_directive(stm->dir_post_head,
                                                    dir_list);
                ret = dir;
            }
            for (dir_list = dir ; dir_list->prev ; dir_list = dir_list->prev)
            ;
            if (dir_list == stm->dir_post_head && stm->ope == OPE_LABEL) {
                stm->dir_post_head = dir->next;
                if (dir->next != NULL) {
                    dir->next->prev = NULL;
                    dir->next = NULL;
                }
                stm->dir_pre_head = dir_link_directive(stm->dir_pre_head,
                                                    dir_list);
                ret = dir;
            }
            else { rep = FALSE; }
        }
    }
    return ret;
}
