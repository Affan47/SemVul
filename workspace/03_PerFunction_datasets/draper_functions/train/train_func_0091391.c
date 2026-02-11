tracker_bus_fd_cursor_real_get_value_type (TrackerSparqlCursor* base, gint column) {
	TrackerBusFDCursor * self;
	TrackerSparqlValueType result = 0;
	gint* _tmp0_;
	gint* _tmp1_;
	gint _tmp2_;
	gint _tmp3_;
#line 54 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	self = (TrackerBusFDCursor*) base;
#line 54 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp0_ = self->types;
#line 54 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	g_return_val_if_fail (_tmp0_ != NULL, 0);
#line 57 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp1_ = self->types;
#line 57 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp2_ = column;
#line 57 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	_tmp3_ = _tmp1_[_tmp2_];
#line 57 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	result = (TrackerSparqlValueType) _tmp3_;
#line 57 "/home/martyn/Source/tracker/src/libtracker-bus/tracker-bus-fd-cursor.vala"
	return result;
#line 229 "tracker-bus-fd-cursor.c"
}
