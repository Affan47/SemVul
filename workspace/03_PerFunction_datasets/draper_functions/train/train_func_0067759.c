replace_target_to_sb(Convert_sb_mt *cvsm)
{
    Block *target = cvsm->to_sb_block, *sb = cvsm->sb, *bpt;
    sb->outer = target->outer;
    sb->module = target->module;

    sb->inner = NULL;

    if (target->prev != NULL) {
        target->prev->next = sb;
        sb->prev = target->prev;
    } else {
        target->outer->inner = sb;
    }

    if (target->next != NULL) {
        target->next->prev = sb;
        sb->next = target->next;
    }

    if ((b_cmp_stasche || cmp_stasche || cmp_ya_templ)
        && sb->outer->hmdf != NULL
        && sb->outer->hmdf->scheduling == SCHE_STATIC) {
        for (bpt = target->inner;
             bpt != NULL && !(bpt->lm_assigned_flg);
             bpt = bpt->next);
        if (bpt != NULL)
            sb->lm_assigned_flg = TRUE;
    }
}
