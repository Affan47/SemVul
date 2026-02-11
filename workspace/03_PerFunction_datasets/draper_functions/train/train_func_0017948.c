transport_deregister_session_configfs(struct se_session *se_sess)
{
	struct se_node_acl *se_nacl;
	unsigned long flags;


	se_nacl = se_sess->se_node_acl;
	if (se_nacl) {
		spin_lock_irqsave(&se_nacl->nacl_sess_lock, flags);
		if (se_nacl->acl_stop == 0)
			list_del(&se_sess->sess_acl_list);


		if (list_empty(&se_nacl->acl_sess_list))
			se_nacl->nacl_sess = NULL;
		else {
			se_nacl->nacl_sess = container_of(
					se_nacl->acl_sess_list.prev,
					struct se_session, sess_acl_list);
		}
		spin_unlock_irqrestore(&se_nacl->nacl_sess_lock, flags);
	}
}
