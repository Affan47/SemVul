cifs_put_smb_ses(struct cifs_ses *ses)
{
	unsigned int rc, xid;
	struct TCP_Server_Info *server = ses->server;

	cifs_dbg(FYI, "%s: ses_count=%d\n", __func__, ses->ses_count);

	spin_lock(&cifs_tcp_ses_lock);
	if (ses->status == CifsExiting) {
		spin_unlock(&cifs_tcp_ses_lock);
		return;
	}
	if (--ses->ses_count > 0) {
		spin_unlock(&cifs_tcp_ses_lock);
		return;
	}
	if (ses->status == CifsGood)
		ses->status = CifsExiting;
	spin_unlock(&cifs_tcp_ses_lock);

	if (ses->status == CifsExiting && server->ops->logoff) {
		xid = get_xid();
		rc = server->ops->logoff(xid, ses);
		if (rc)
			cifs_dbg(VFS, "%s: Session Logoff failure rc=%d\n",
				__func__, rc);
		_free_xid(xid);
	}

	spin_lock(&cifs_tcp_ses_lock);
	list_del_init(&ses->smb_ses_list);
	spin_unlock(&cifs_tcp_ses_lock);

	sesInfoFree(ses);
	cifs_put_tcp_session(server, 0);
}
