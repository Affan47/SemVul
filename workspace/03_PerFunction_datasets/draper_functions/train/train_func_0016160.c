search_kick_group(List *head,
                  int mt_no,
                  Dtu_timing timing,
                  int pg_no)
{
    List *l;

    for (l = head; l != NULL; l = l->next) {
        Kick_group *kickg = l->data;

        if (kickg->kick_mt->mt_no == mt_no
            && kickg->kick_mt->timing == timing
            && (pg_no == -1 || (kickg->kick_mt->pc_no == pg_no)))
            return kickg;
    }
    return NULL;
}
