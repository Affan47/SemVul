dlr_entry_duplicate(const struct dlr_entry *dlr)
{
    struct dlr_entry *ret;

    if (dlr == NULL)
        return NULL;

    ret = dlr_entry_create();
    ret->smsc = octstr_duplicate(dlr->smsc);
    ret->timestamp = octstr_duplicate(dlr->timestamp);
    ret->source = octstr_duplicate(dlr->source);
    ret->destination = octstr_duplicate(dlr->destination);
    ret->service = octstr_duplicate(dlr->service);
    ret->url = octstr_duplicate(dlr->url);
    ret->boxc_id = octstr_duplicate(dlr->boxc_id);
    ret->mask = dlr->mask;

    return ret;
}
