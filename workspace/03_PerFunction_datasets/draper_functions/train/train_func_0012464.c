auth_accounts_construct (GType object_type) {
	AuthAccounts * self;
	GeeArrayList* _tmp0_;
	self = (AuthAccounts*) g_object_new (object_type, NULL);
	self->priv->acc_lst = (_tmp0_ = gee_array_list_new (AUTH_TYPE_ACCOUNT, (GBoxedCopyFunc) g_object_ref, g_object_unref, NULL), _g_object_unref0 (self->priv->acc_lst), _tmp0_);
	auth_accounts_load (self);
	return self;
}
