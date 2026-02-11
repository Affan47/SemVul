dvb_schedule_get_overlapping_events (DVBSchedule* self, DVBEvent* event) {
	GeeList* result = NULL;
	GeeList* elements = NULL;
	DVBEventStorage* _tmp0_ = NULL;
	DVBEvent* _tmp1_ = NULL;
	GeeList* _tmp2_ = NULL;
	GeeList* overlap = NULL;
	GeeArrayList* _tmp3_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (event != NULL, NULL);
	_tmp0_ = self->priv->events;
	_tmp1_ = event;
	_tmp2_ = dvb_event_storage_get_overlapping_events (_tmp0_, _tmp1_);
	elements = _tmp2_;
	_tmp3_ = gee_array_list_new (DVB_TYPE_EVENT, (GBoxedCopyFunc) dvb_event_ref, dvb_event_unref, NULL);
	overlap = (GeeList*) _tmp3_;
	{
		GeeList* _data_list = NULL;
		GeeList* _tmp4_ = NULL;
		GeeList* _tmp5_ = NULL;
		gint _data_size = 0;
		GeeList* _tmp6_ = NULL;
		gint _tmp7_ = 0;
		gint _tmp8_ = 0;
		gint _data_index = 0;
		_tmp4_ = elements;
		_tmp5_ = _g_object_ref0 (_tmp4_);
		_data_list = _tmp5_;
		_tmp6_ = _data_list;
		_tmp7_ = gee_collection_get_size ((GeeCollection*) _tmp6_);
		_tmp8_ = _tmp7_;
		_data_size = _tmp8_;
		_data_index = -1;
		while (TRUE) {
			gint _tmp9_ = 0;
			gint _tmp10_ = 0;
			gint _tmp11_ = 0;
			DVBEventElement* data = NULL;
			GeeList* _tmp12_ = NULL;
			gint _tmp13_ = 0;
			gpointer _tmp14_ = NULL;
			DVBEvent* e = NULL;
			DVBEventElement* _tmp15_ = NULL;
			guint _tmp16_ = 0U;
			DVBEvent* _tmp17_ = NULL;
			gboolean _tmp18_ = FALSE;
			DVBEvent* _tmp19_ = NULL;
			gboolean _tmp23_ = FALSE;
			_tmp9_ = _data_index;
			_data_index = _tmp9_ + 1;
			_tmp10_ = _data_index;
			_tmp11_ = _data_size;
			if (!(_tmp10_ < _tmp11_)) {
				break;
			}
			_tmp12_ = _data_list;
			_tmp13_ = _data_index;
			_tmp14_ = gee_list_get (_tmp12_, _tmp13_);
			data = (DVBEventElement*) _tmp14_;
			_tmp15_ = data;
			_tmp16_ = _tmp15_->id;
			_tmp17_ = dvb_schedule_get_event (self, _tmp16_);
			e = _tmp17_;
			_tmp19_ = e;
			if (_tmp19_ != NULL) {
				DVBEvent* _tmp20_ = NULL;
				DVBEvent* _tmp21_ = NULL;
				gdouble _tmp22_ = 0.0;
				_tmp20_ = e;
				_tmp21_ = event;
				_tmp22_ = dvb_event_get_overlap_percentage (_tmp20_, _tmp21_);
				_tmp18_ = _tmp22_ >= DVB_SCHEDULE_MIN_EVENT_OVERLAP;
			} else {
				_tmp18_ = FALSE;
			}
			_tmp23_ = _tmp18_;
			if (_tmp23_) {
				GeeList* _tmp24_ = NULL;
				DVBEvent* _tmp25_ = NULL;
				_tmp24_ = overlap;
				_tmp25_ = e;
				gee_collection_add ((GeeCollection*) _tmp24_, _tmp25_);
			}
			_dvb_event_unref0 (e);
			_g_object_unref0 (data);
		}
		_g_object_unref0 (_data_list);
	}
	result = overlap;
	_g_object_unref0 (elements);
	return result;
}
