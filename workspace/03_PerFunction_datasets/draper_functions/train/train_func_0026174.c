tile_matches (Tile* self, Tile* tile) {
	gboolean result = FALSE;
	Tile* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	gint _tmp4_ = 0;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (tile != NULL, FALSE);
	_tmp0_ = tile;
	_tmp1_ = tile_get_set (_tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = tile_get_set (self);
	_tmp4_ = _tmp3_;
	result = _tmp2_ == _tmp4_;
	return result;
}
