dvb_event_storage_get (DVBEventStorage* self, gint index) {
	DVBEventElement* result = NULL;
	gint _tmp0_ = 0;
	GSequence* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	GSequenceIter* iter = NULL;
	GSequence* _tmp3_ = NULL;
	gint _tmp4_ = 0;
	GSequenceIter* _tmp5_ = NULL;
	DVBEventElement* element = NULL;
	GSequence* _tmp6_ = NULL;
	gconstpointer _tmp7_ = NULL;
	DVBEventElement* _tmp8_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = index;
	_tmp1_ = self->priv->events;
	_tmp2_ = g_sequence_get_length (_tmp1_);
	_vala_assert (_tmp0_ < _tmp2_, "index < this.events.get_length ()");
	_tmp3_ = self->priv->events;
	_tmp4_ = index;
	_tmp5_ = g_sequence_get_iter_at_pos (_tmp3_, _tmp4_);
	iter = _tmp5_;
	_tmp6_ = self->priv->events;
	_tmp7_ = g_sequence_get (iter);
	_tmp8_ = _g_object_ref0 ((DVBEventElement*) _tmp7_);
	element = _tmp8_;
	result = element;
	return result;
}
