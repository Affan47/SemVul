gee_map_remove (GeeMap* self, gconstpointer key, gpointer* value) {
	gpointer _vala_value = NULL;
	gboolean result = FALSE;
	gconstpointer _tmp0_ = NULL;
	gpointer _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	_tmp0_ = key;
	_tmp2_ = gee_map_unset (self, _tmp0_, &_tmp1_);
	((_vala_value == NULL) || (GEE_MAP_GET_INTERFACE (self)->get_v_destroy_func (self) == NULL)) ? NULL : (_vala_value = (GEE_MAP_GET_INTERFACE (self)->get_v_destroy_func (self) (_vala_value), NULL));
	_vala_value = _tmp1_;
	result = _tmp2_;
	if (value) {
		*value = _vala_value;
	} else {
		((_vala_value == NULL) || (GEE_MAP_GET_INTERFACE (self)->get_v_destroy_func (self) == NULL)) ? NULL : (_vala_value = (GEE_MAP_GET_INTERFACE (self)->get_v_destroy_func (self) (_vala_value), NULL));
	}
	return result;
}
