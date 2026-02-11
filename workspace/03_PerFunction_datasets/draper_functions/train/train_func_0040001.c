journal_close_file(journal_t *journal)
{

	if (journal == NULL) {
		return KNOT_EINVAL;
	}


	int ret = journal_update_crc(journal->fd);


	close(journal->fd);
	journal->fd = -1;


	free(journal->nodes);
	journal->nodes = NULL;

	dbg_journal("journal: closed journal %p\n", journal);

	return ret;
}
