search_target_sb_head(Block *bpt, IntSet mark)
{
    Block *sb;

    if ((bpt->dlg_tag == DLG_HEAD_NO
         || bpt->car_tag == CAR_HEAD_NO)
        && bpt->kind == SB
        && in_IntSet(mark, bpt->no)) {
        add1_IntSet(mark, bpt->no);
        return bpt;
    }

    for (sb = bpt->next; sb != NULL; sb = sb->next) {
        if (sb->kind == SB && !in_IntSet(mark, sb->no)) {
            add1_IntSet(mark, sb->no);
            return sb;
        }
    }

    return NULL;
}
