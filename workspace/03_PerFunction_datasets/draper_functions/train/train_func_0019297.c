__lambda10_ (CaribouLevelModel* self, CaribouKeyModel* k) {
	CaribouKeyModel* _tmp0_ = NULL;
	g_return_if_fail (k != NULL);
	_tmp0_ = k;
	g_signal_emit_by_name ((CaribouIKeyboardObject*) self, "key-released", _tmp0_);
}
