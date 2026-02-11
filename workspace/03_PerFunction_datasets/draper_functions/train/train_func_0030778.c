smb2_is_valid_lease_break(char *buffer)
{
	struct smb2_lease_break *rsp = (struct smb2_lease_break *)buffer;
	struct list_head *tmp, *tmp1, *tmp2;
	struct TCP_Server_Info *server;
	struct cifs_ses *ses;
	struct cifs_tcon *tcon;
	struct smb2_lease_break_work *lw;

	lw = kmalloc(sizeof(struct smb2_lease_break_work), GFP_KERNEL);
	if (!lw)
		return false;

	INIT_WORK(&lw->lease_break, cifs_ses_oplock_break);
	lw->lease_state = rsp->NewLeaseState;

	cifs_dbg(FYI, "Checking for lease break\n");


	spin_lock(&cifs_tcp_ses_lock);
	list_for_each(tmp, &cifs_tcp_ses_list) {
		server = list_entry(tmp, struct TCP_Server_Info, tcp_ses_list);

		list_for_each(tmp1, &server->smb_ses_list) {
			ses = list_entry(tmp1, struct cifs_ses, smb_ses_list);

			list_for_each(tmp2, &ses->tcon_list) {
				tcon = list_entry(tmp2, struct cifs_tcon,
						  tcon_list);
				spin_lock(&tcon->open_file_lock);
				cifs_stats_inc(
				    &tcon->stats.cifs_stats.num_oplock_brks);
				if (smb2_tcon_has_lease(tcon, rsp, lw)) {
					spin_unlock(&tcon->open_file_lock);
					spin_unlock(&cifs_tcp_ses_lock);
					return true;
				}
				spin_unlock(&tcon->open_file_lock);
			}
		}
	}
	spin_unlock(&cifs_tcp_ses_lock);
	kfree(lw);
	cifs_dbg(FYI, "Can not process lease break - no lease matched\n");
	return false;
}
