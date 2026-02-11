append_new_trans_entry(List *group,
                       Block *pred, Block *target,
                       int srcpe, int dstpe,
                       TransType type,
                       Array_def_use_table_semnode* data,
                       real cost)
{
    TE *new_entry;
    TE *ept;
    TG *gpt;

    new_entry = zcalloc(1, sizeof(TE));
    if (pred != NULL) {
        new_entry->srcmt = pred->hmt_no;
    } else {
        new_entry->srcmt = -1;
    }
    if (target != NULL) {
        new_entry->dstmt = target->hmt_no;
    } else {
        new_entry->dstmt = -1;
    }

    gpt = (TG *)(group->data);
    if (gpt->entry == NULL) {
        gpt->entry = new_entry;
    } else {
        for (ept = gpt->entry; ept->next != NULL; ept = ept->next) ;
        ept->next = new_entry;
    }

    new_entry->srcpe = srcpe;
    new_entry->dstpe = dstpe;
    new_entry->type = type;
    new_entry->data = copy_array_def_use_table_semnode(data);
    new_entry->cost = cost;
    new_entry->starttime = gpt->endtime;
    new_entry->endtime = gpt->endtime + cost;
    new_entry->group = gpt;
    gpt->endtime += cost;
}
