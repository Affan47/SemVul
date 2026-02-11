make_dosum_info_for_doacross(StripMining *sm, Loop *sm_loop)
{
    List       *li;
    Dosum_info *p;
    Dosum_info *head = NULL;

    if (sm->flg_doacross) {
        for (li = sm->loops; li != NULL; li = li->next) {
            StripMiningInnerLoop *smil = li->data;

            if (smil->org_kind == DOSUM) {
                for (p = smil->block->dosum_info; p; p = p->next) {
                    Dosum_info *di = copy_dosum_info(p);
                    di->qr_sum = NULL;
                    head = append_dosum_info(head, di);
                }
            }
        }
    }

    sm_loop->block->dosum_info = head;

}
