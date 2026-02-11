dlr_entry_destroy(struct dlr_entry *dlr)
{

    if (dlr == NULL)
        return;

#define O_DELETE(a)	 { if (a) octstr_destroy(a); a = NULL; }

    O_DELETE(dlr->smsc);
    O_DELETE(dlr->timestamp);
    O_DELETE(dlr->source);
    O_DELETE(dlr->destination);
    O_DELETE(dlr->service);
    O_DELETE(dlr->url);
    O_DELETE(dlr->boxc_id);

#undef O_DELETE

    dlr->mask = 0;
    gw_free(dlr);
}
