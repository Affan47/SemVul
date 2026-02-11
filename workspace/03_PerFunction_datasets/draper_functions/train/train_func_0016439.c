slurmdbd_free_acct_coord_msg(dbd_acct_coord_msg_t *msg)
{
	if (msg) {
		if (msg->acct_list) {
			list_destroy(msg->acct_list);
			msg->acct_list = NULL;
		}
		slurmdb_destroy_user_cond(msg->cond);
		xfree(msg);
	}
}
