_index_search(unsigned **msgno_list, struct index_state *state,
			 struct searchargs *searchargs,
			 modseq_t *highestmodseq)
{
    uint32_t msgno;
    struct mapfile msgfile;
    int n = 0;
    int listindex, min;
    int listcount;
    struct mailbox *mailbox = state->mailbox;
    struct index_map *im;

    if (state->exists <= 0) return 0;

    *msgno_list = (unsigned *) xmalloc(state->exists * sizeof(unsigned));


    listcount = search_prefilter_messages(*msgno_list, state, searchargs);

    if (searchargs->returnopts == SEARCH_RETURN_MAX) {


	listindex = listcount;
	min = 0;
    } else {

	listindex = 0;
	min = listcount;
    }


    for (; listindex < listcount; listindex++) {
	msgno = (*msgno_list)[listindex];
	im = &state->map[msgno-1];
	msgfile.base = 0;
	msgfile.size = 0;


	if (im->record.system_flags & FLAG_EXPUNGED)
	    continue;

	if (index_search_evaluate(state, searchargs, msgno, &msgfile)) {
	    (*msgno_list)[n++] = msgno;
	    if (highestmodseq && im->record.modseq > *highestmodseq) {
		*highestmodseq = im->record.modseq;
	    }


	    if ((searchargs->returnopts & SEARCH_RETURN_MIN) &&
		!(searchargs->returnopts & SEARCH_RETURN_COUNT) &&
		!(searchargs->returnopts & SEARCH_RETURN_ALL)) {

		if (searchargs->returnopts & SEARCH_RETURN_MAX) {

		    min = listindex;
		}

		listindex = listcount;
		if (highestmodseq)
		    *highestmodseq = im->record.modseq;
	    }
	}
	if (msgfile.base) {
	    mailbox_unmap_message(mailbox, im->record.uid,
				  &msgfile.base, &msgfile.size);
	}
    }


    for (listindex = listcount; listindex > min; listindex--) {
	msgno = (*msgno_list)[listindex-1];
	im = &state->map[msgno-1];
	msgfile.base = 0;
	msgfile.size = 0;


	if (im->record.system_flags & FLAG_EXPUNGED)
	    continue;

	if (index_search_evaluate(state, searchargs, msgno, &msgfile)) {
	    (*msgno_list)[n++] = msgno;
	    if (highestmodseq && im->record.modseq > *highestmodseq) {
		*highestmodseq = im->record.modseq;
	    }

	    listindex = 0;
	}
	if (msgfile.base) {
	    mailbox_unmap_message(mailbox, im->record.uid,
				  &msgfile.base, &msgfile.size);
	}
    }


    if (!n && *msgno_list) {
	free(*msgno_list);
	*msgno_list = NULL;
    }

    return n;
}
