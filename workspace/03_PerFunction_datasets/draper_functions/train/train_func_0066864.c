dvb_channel_list_get_channel (DVBChannelList* self, guint sid) {
	DVBChannel* result = NULL;
	DVBChannel* val = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	val = NULL;
	{
		GeeHashMap* _tmp0_ = NULL;
		_tmp0_ = self->channels;
		g_rec_mutex_lock (&self->priv->__lock_channels);
		{
			GeeHashMap* _tmp1_ = NULL;
			guint _tmp2_ = 0U;
			gboolean _tmp3_ = FALSE;
			_tmp1_ = self->channels;
			_tmp2_ = sid;
			_tmp3_ = gee_abstract_map_has_key ((GeeAbstractMap*) _tmp1_, (gpointer) ((guintptr) _tmp2_));
			if (_tmp3_) {
				GeeHashMap* _tmp4_ = NULL;
				guint _tmp5_ = 0U;
				gpointer _tmp6_ = NULL;
				_tmp4_ = self->channels;
				_tmp5_ = sid;
				_tmp6_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp4_, (gpointer) ((guintptr) _tmp5_));
				_g_object_unref0 (val);
				val = (DVBChannel*) _tmp6_;
			}
		}
		__finally33:
		{
			GeeHashMap* _tmp7_ = NULL;
			_tmp7_ = self->channels;
			g_rec_mutex_unlock (&self->priv->__lock_channels);
		}
		if (_inner_error_ != NULL) {
			_g_object_unref0 (val);
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	result = val;
	return result;
}
