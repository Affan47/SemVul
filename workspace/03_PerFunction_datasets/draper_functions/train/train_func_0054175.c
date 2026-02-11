jbd2_journal_ack_err(journal_t *journal)
{
	write_lock(&journal->j_state_lock);
	if (journal->j_errno)
		journal->j_flags |= JBD2_ACK_ERR;
	write_unlock(&journal->j_state_lock);
}
