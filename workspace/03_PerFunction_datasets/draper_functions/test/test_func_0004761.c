fso_gsm_abstract_modem_real_channel (FsoGsmAbstractModem* self, const gchar* category) {
	FsoGsmChannel* result = NULL;
	GeeHashMap* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	const gchar* _tmp3_ = NULL;
	g_return_val_if_fail (category != NULL, NULL);
	_tmp0_ = self->channels;
	_tmp1_ = gee_abstract_map_get_size ((GeeMap*) _tmp0_);
	_tmp2_ = _tmp1_;
	if (_tmp2_ == 0) {
		result = NULL;
		return result;
	}
	_tmp3_ = category;
	if (g_strcmp0 (_tmp3_, "") == 0) {
		{
			GeeIterator* _chan_it = NULL;
			GeeHashMap* _tmp4_ = NULL;
			GeeCollection* _tmp5_ = NULL;
			GeeCollection* _tmp6_ = NULL;
			GeeCollection* _tmp7_ = NULL;
			GeeIterator* _tmp8_ = NULL;
			GeeIterator* _tmp9_ = NULL;
			_tmp4_ = self->channels;
			_tmp5_ = gee_abstract_map_get_values ((GeeMap*) _tmp4_);
			_tmp6_ = _tmp5_;
			_tmp7_ = _tmp6_;
			_tmp8_ = gee_iterable_iterator ((GeeIterable*) _tmp7_);
			_tmp9_ = _tmp8_;
			_g_object_unref0 (_tmp7_);
			_chan_it = _tmp9_;
			while (TRUE) {
				GeeIterator* _tmp10_ = NULL;
				gboolean _tmp11_ = FALSE;
				FsoGsmChannel* chan = NULL;
				GeeIterator* _tmp12_ = NULL;
				gpointer _tmp13_ = NULL;
				_tmp10_ = _chan_it;
				_tmp11_ = gee_iterator_next (_tmp10_);
				if (!_tmp11_) {
					break;
				}
				_tmp12_ = _chan_it;
				_tmp13_ = gee_iterator_get (_tmp12_);
				chan = (FsoGsmChannel*) _tmp13_;
				result = chan;
				_g_object_unref0 (_chan_it);
				return result;
			}
			_g_object_unref0 (_chan_it);
		}
	} else {
		GeeHashMap* _tmp14_ = NULL;
		const gchar* _tmp15_ = NULL;
		gpointer _tmp16_ = NULL;
		_tmp14_ = self->channels;
		_tmp15_ = category;
		_tmp16_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp14_, _tmp15_);
		result = (FsoGsmChannel*) _tmp16_;
		return result;
	}
	result = NULL;
	return result;
}
