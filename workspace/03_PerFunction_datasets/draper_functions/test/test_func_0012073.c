game_get_can_redo (Game* self) {
	gboolean result;
	GList* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, FALSE);
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
				gint _tmp3_ = 0;
				gint _tmp4_ = 0;
				_tmp2_ = tile;
				_tmp3_ = _tmp2_->move_number;
				_tmp4_ = self->move_number;
				if (_tmp3_ >= _tmp4_) {
					result = TRUE;
					_tile_unref0 (tile);
					return result;
				}
				_tile_unref0 (tile);
			}
		}
	}
	result = FALSE;
	return result;
}
