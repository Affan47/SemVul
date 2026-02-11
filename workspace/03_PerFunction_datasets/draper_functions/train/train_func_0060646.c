collect_dosum_info(const StripMining *sm, Boolean flg_position, int position)
{
    List *li;
    Block *b;
    StripMiningInnerLoop *smil;
    Dosum_info *head = NULL;
    Dosum_info *p;

    for (li = sm->loops; li != NULL; li = li->next) {
        smil = SMIL(li->data);

        if (flg_position && smil->position != position)
            continue;

        b = smil->block;
        if (b->kind == DOSUM) {
            for (p = b->dosum_info; p != NULL; p = p->next) {
                Dosum_info *tmp = copy_dosum_info(p);
                tmp->qr_sum = NULL;
                head = append_dosum_info(head, tmp);
            }
        }
    }

    return head;
}
