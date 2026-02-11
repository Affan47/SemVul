_tpf_persona_store_update_avatar_cache (TpfPersonaStore* self, const gchar* persona_iid, GFile* avatar_file) {
	GFile* _tmp0_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (persona_iid != NULL);
	_tmp0_ = avatar_file;
	if (_tmp0_ == NULL) {
		GeeHashMap* _tmp1_ = NULL;
		const gchar* _tmp2_ = NULL;
		_tmp1_ = self->priv->_avatars;
		_tmp2_ = persona_iid;
		gee_abstract_map_unset ((GeeAbstractMap*) _tmp1_, _tmp2_, NULL);
	} else {
		GeeHashMap* _tmp3_ = NULL;
		const gchar* _tmp4_ = NULL;
		GFile* _tmp5_ = NULL;
		_tmp3_ = self->priv->_avatars;
		_tmp4_ = persona_iid;
		_tmp5_ = avatar_file;
		gee_abstract_map_set ((GeeAbstractMap*) _tmp3_, _tmp4_, G_TYPE_CHECK_INSTANCE_CAST (_tmp5_, G_TYPE_FILE, GFile));
	}
}
