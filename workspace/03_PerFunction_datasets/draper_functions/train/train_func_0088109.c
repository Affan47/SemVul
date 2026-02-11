ldap_op_finished (LDAPOp *op)
{
	EBookBackend *backend = op->backend;
	EBookBackendLDAP *bl = E_BOOK_BACKEND_LDAP (backend);

	g_rec_mutex_lock (&eds_ldap_handler_lock);
	g_rec_mutex_lock (&bl->priv->op_hash_mutex);
	g_hash_table_remove (bl->priv->id_to_op, &op->id);


	book_view_notify_status (bl, find_book_view (bl), "");


	if (bl->priv->ldap)
		ldap_abandon (bl->priv->ldap, op->id);

	if (op->dtor)
		op->dtor (op);

	bl->priv->active_ops--;

	if (bl->priv->active_ops == 0) {
		if (bl->priv->poll_timeout > 0) {
			g_source_remove (bl->priv->poll_timeout);
			bl->priv->poll_timeout = 0;
		}
	}
	g_rec_mutex_unlock (&bl->priv->op_hash_mutex);
	g_rec_mutex_unlock (&eds_ldap_handler_lock);
}
