update_readyset(Stasche *sinfo)
{
    int i;

    clear_IntSet(sinfo->readyset);
    for (i = 1; i <= sinfo->mt_num; i++) {
        if (!in_IntSet(sinfo->taskf, i)
            && !test_subtract_IntSet(sinfo->block[i]->pred, sinfo->taskf)) {
            add1_IntSet(sinfo->readyset, i);
        }
    }
}
