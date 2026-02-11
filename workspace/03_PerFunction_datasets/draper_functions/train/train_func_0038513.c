show_candidate(book, pos0)
    EB_Book *book;
    EB_Position pos0;
{
    char buf[2048];
    ssize_t buflen;
    struct multi_can *child, *ptail;
    EB_Error_Code error_code = EB_SUCCESS;

    eb_initialize_hookset (&multi_candidate_hookset);
    eb_set_hooks (&multi_candidate_hookset, multi_candidate_hooks);

    error_code = eb_seek_text(book, &pos0);
    if (error_code != EB_SUCCESS) {
        xprintf("An error occured in seek_position: %s\n",
	       eb_error_message(error_code));
	set_error_message (error_code);
	return 0;
    }
    error_code = eb_read_text(book, 0, &multi_candidate_hookset, NULL,
			      2047, buf, &buflen);
    if (error_code != EB_SUCCESS) {
        xprintf("An error occured in read_text: %s\n",
	       eb_error_message(error_code));
	set_error_message (error_code);
	return 0;
    }
#if MULTI_DEBUG
    xprintf(">> buflen = %ld\n", (long)buflen);
#endif

    tail->terminated = 1;

    while ((child = find_child(head)) != 0) {
	ptail = tail;
#if MULTI_DEBUG
	xprintf(">> current tail %s:%d->next %s:%d\n",
		tail->text, tail,
		tail->next->text, tail->next);
#endif
	process_child(book, child);
	child->child = ptail->next;
    }

    show_candidates_level(head, 0);

    free_candidates_tree(head);
    head = 0;
    tail = 0;

    return 1;
}
