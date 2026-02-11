mailbox_copy_files(struct mailbox *mailbox, const char *newpart,
		       const char *newname)
{
    char oldbuf[MAX_MAILBOX_PATH], newbuf[MAX_MAILBOX_PATH];
    const char *path;
    struct meta_file *mf;
    uint32_t recno;
    struct index_record record;
    int r;


    path = mboxname_datapath(newpart, newname, 0);
    cyrus_mkdir(path, 0755);
    mkdir(path, 0755);
    path = mboxname_metapath(newpart, newname, 0, 0);
    cyrus_mkdir(path, 0755);
    mkdir(path, 0755);


    for (mf = meta_files; mf->metaflag; mf++) {
	struct stat sbuf;

	strncpy(oldbuf, mailbox_meta_fname(mailbox, mf->metaflag),
		MAX_MAILBOX_PATH);
	strncpy(newbuf, mboxname_metapath(newpart, newname, mf->metaflag, 0),
		MAX_MAILBOX_PATH);

	unlink(newbuf);

	if (!mf->optional || stat(oldbuf, &sbuf) != -1) {
	    r = mailbox_copyfile(oldbuf, newbuf, mf->nolink);
	    if (r) return r;
	}
    }

    for (recno = 1; recno <= mailbox->i.num_records; recno++) {
	r = mailbox_read_index_record(mailbox, recno, &record);
	if (r) return r;

	if (record.system_flags & FLAG_UNLINKED)
	    continue;

	strncpy(oldbuf, mailbox_message_fname(mailbox, record.uid),
		MAX_MAILBOX_PATH);
	strncpy(newbuf, mboxname_datapath(newpart, newname, record.uid),
		MAX_MAILBOX_PATH);

	r = mailbox_copyfile(oldbuf, newbuf, 0);
	if (r) return r;
    }

    return 0;
}
