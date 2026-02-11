reset_transaction(struct dundi_transaction *trans)
{
	int tid;
	tid = get_trans_id();
	if (tid < 1)
		return -1;
	trans->strans = tid;
	trans->dtrans = 0;
	trans->iseqno = 0;
	trans->oiseqno = 0;
	trans->oseqno = 0;
	trans->aseqno = 0;
	ast_clear_flag(trans, FLAG_FINAL);
	return 0;
}
