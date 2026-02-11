nfs4_alloc_session(struct nfs_client *clp)
{
	struct nfs4_session *session;

	session = kzalloc(sizeof(struct nfs4_session), GFP_NOFS);
	if (!session)
		return NULL;

	nfs4_init_slot_table(&session->fc_slot_table, "ForeChannel Slot table");
	nfs4_init_slot_table(&session->bc_slot_table, "BackChannel Slot table");
	session->session_state = 1<<NFS4_SESSION_INITING;

	session->clp = clp;
	return session;
}
