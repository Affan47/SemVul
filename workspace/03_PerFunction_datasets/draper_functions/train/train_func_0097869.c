expire_cb(struct mailbox *mailbox __attribute__((unused)),
			  struct index_record *record,
			  void *rock)
{
    struct expire_rock *erock = (struct expire_rock *) rock;

    erock->messages++;


    if (record->gmtime < erock->expire_mark) {
	erock->deleted++;
	return 1;
    }

    return 0;
}
