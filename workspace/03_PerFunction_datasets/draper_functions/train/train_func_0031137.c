dvb_recordings_store_update_last_id (DVBRecordingsStore* self, guint32 new_last_id) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	{
		GeeHashMap* _tmp0_ = NULL;
		_tmp0_ = self->priv->recordings;
		g_rec_mutex_lock (&self->priv->__lock_recordings);
		{
			guint32 _tmp1_ = 0U;
			guint32 _tmp2_ = 0U;
			_tmp1_ = new_last_id;
			_tmp2_ = self->priv->last_id;
			if (_tmp1_ > _tmp2_) {
				guint32 _tmp3_ = 0U;
				_tmp3_ = new_last_id;
				self->priv->last_id = _tmp3_;
			}
		}
		__finally137:
		{
			GeeHashMap* _tmp4_ = NULL;
			_tmp4_ = self->priv->recordings;
			g_rec_mutex_unlock (&self->priv->__lock_recordings);
		}
		if (_inner_error_ != NULL) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
}
