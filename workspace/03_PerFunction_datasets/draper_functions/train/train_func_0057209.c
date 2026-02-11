unity_protocol_music_preview_real_add_properties (UnityProtocolPreview* base, GHashTable* properties) {
	UnityProtocolMusicPreview * self;
	GHashTable* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp6_ = NULL;
	DeeSerializableModel* _tmp11_ = NULL;
	self = (UnityProtocolMusicPreview*) base;
	g_return_if_fail (properties != NULL);
	_tmp0_ = properties;
	UNITY_PROTOCOL_PREVIEW_CLASS (unity_protocol_music_preview_parent_class)->add_properties (G_TYPE_CHECK_INSTANCE_CAST (self, UNITY_PROTOCOL_TYPE_PREVIEW, UnityProtocolPreview), _tmp0_);
	_tmp1_ = self->priv->_track_data_swarm_name;
	if (_tmp1_ != NULL) {
		GHashTable* _tmp2_ = NULL;
		gchar* _tmp3_ = NULL;
		const gchar* _tmp4_ = NULL;
		GVariant* _tmp5_ = NULL;
		_tmp2_ = properties;
		_tmp3_ = g_strdup ("track-data-swarm-name");
		_tmp4_ = self->priv->_track_data_swarm_name;
		_tmp5_ = _variant_new17 (_tmp4_);
		g_hash_table_insert (_tmp2_, _tmp3_, _tmp5_);
	}
	_tmp6_ = self->priv->_track_data_address;
	if (_tmp6_ != NULL) {
		GHashTable* _tmp7_ = NULL;
		gchar* _tmp8_ = NULL;
		const gchar* _tmp9_ = NULL;
		GVariant* _tmp10_ = NULL;
		_tmp7_ = properties;
		_tmp8_ = g_strdup ("track-data-address");
		_tmp9_ = self->priv->_track_data_address;
		_tmp10_ = _variant_new18 (_tmp9_);
		g_hash_table_insert (_tmp7_, _tmp8_, _tmp10_);
	}
	_tmp11_ = self->priv->_track_model;
	if (_tmp11_ != NULL) {
		GHashTable* _tmp12_ = NULL;
		gchar* _tmp13_ = NULL;
		DeeSerializableModel* _tmp14_ = NULL;
		GVariant* _tmp15_ = NULL;
		_tmp12_ = properties;
		_tmp13_ = g_strdup ("track-model");
		_tmp14_ = self->priv->_track_model;
		_tmp15_ = dee_serializable_serialize ((DeeSerializable*) _tmp14_);
		g_hash_table_insert (_tmp12_, _tmp13_, _tmp15_);
	}
}
