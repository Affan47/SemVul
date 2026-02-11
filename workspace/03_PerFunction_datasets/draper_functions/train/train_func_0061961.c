game_get_visible_tiles (Game* self) {
	gint result;
	gint n = 0;
	GList* _tmp0_ = NULL;
	gint _tmp5_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	n = 0;
	_tmp0_ = self->tiles;
	{
		GList* tile_collection = NULL;
		GList* tile_it = NULL;
		tile_collection = _tmp0_;
		for (tile_it = tile_collection; tile_it != NULL; tile_it = tile_it->next) {
			Tile* _tmp1_ = NULL;
			Tile* tile = NULL;
			_tmp1_ = _tile_ref0 ((Tile*) tile_it->data);
			tile = _tmp1_;
			{
				Tile* _tmp2_ = NULL;
				gboolean _tmp3_ = FALSE;
				_tmp2_ = tile;
				_tmp3_ = _tmp2_->visible;
				if (_tmp3_) {
					gint _tmp4_ = 0;
					_tmp4_ = n;
					n = _tmp4_ + 1;
				}
				_tile_unref0 (tile);
			}
		}
	}
	_tmp5_ = n;
	result = _tmp5_;
	return result;
}
