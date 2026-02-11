index_copysetup(struct index_state *state, uint32_t msgno,
			   struct copyargs *copyargs)
{
    int flag = 0;
    int userflag;
    bit32 flagmask = 0;
    int r;
    struct mailbox *mailbox = state->mailbox;
    struct index_map *im = &state->map[msgno-1];

    r = mailbox_cacherecord(mailbox, &im->record);
    if (r) return r;

    if (copyargs->nummsg == copyargs->msgalloc) {
	copyargs->msgalloc += COPYARGSGROW;
	copyargs->copymsg = (struct copymsg *)
	  xrealloc((char *)copyargs->copymsg,
		   copyargs->msgalloc * sizeof(struct copymsg));
    }

    copyargs->copymsg[copyargs->nummsg].uid = im->record.uid;
    copyargs->copymsg[copyargs->nummsg].internaldate = im->record.internaldate;
    copyargs->copymsg[copyargs->nummsg].sentdate = im->record.sentdate;
    copyargs->copymsg[copyargs->nummsg].gmtime = im->record.gmtime;
    copyargs->copymsg[copyargs->nummsg].size = im->record.size;
    copyargs->copymsg[copyargs->nummsg].header_size = im->record.header_size;
    copyargs->copymsg[copyargs->nummsg].content_lines = im->record.content_lines;
    copyargs->copymsg[copyargs->nummsg].cache_version = im->record.cache_version;
    copyargs->copymsg[copyargs->nummsg].cache_crc = im->record.cache_crc;
    copyargs->copymsg[copyargs->nummsg].crec = im->record.crec;

    message_guid_copy(&copyargs->copymsg[copyargs->nummsg].guid,
		      &im->record.guid);

    copyargs->copymsg[copyargs->nummsg].system_flags = im->record.system_flags;
    for (userflag = 0; userflag < MAX_USER_FLAGS; userflag++) {
	if ((userflag & 31) == 0) {
	    flagmask = im->record.user_flags[userflag/32];
	}
	if (mailbox->flagname[userflag] && (flagmask & (1<<(userflag&31)))) {
	    copyargs->copymsg[copyargs->nummsg].flag[flag++] =
		mailbox->flagname[userflag];
	}
    }
    copyargs->copymsg[copyargs->nummsg].flag[flag] = 0;


    copyargs->copymsg[copyargs->nummsg].seen = im->isseen;

    copyargs->nummsg++;

    return 0;
}
