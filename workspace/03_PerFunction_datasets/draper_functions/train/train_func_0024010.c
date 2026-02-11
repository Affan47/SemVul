puzzle_get_tile_location (Puzzle* self, Tile* tile, guint* x, guint* y) {
	guint _vala_x = 0U;
	guint _vala_y = 0U;
	guint _tmp0_;
	g_return_if_fail (self != NULL);
	g_return_if_fail (tile != NULL);
	_vala_y = (guint) 0;
	_tmp0_ = _vala_y;
	_vala_x = _tmp0_;
	{
		gboolean _tmp1_;
		_vala_x = (guint) 0;
		_tmp1_ = TRUE;
		while (TRUE) {
			gboolean _tmp2_;
			guint _tmp4_;
			guint _tmp5_;
			guint _tmp6_;
			_tmp2_ = _tmp1_;
			if (!_tmp2_) {
				guint _tmp3_;
				_tmp3_ = _vala_x;
				_vala_x = _tmp3_ + 1;
			}
			_tmp1_ = FALSE;
			_tmp4_ = _vala_x;
			_tmp5_ = puzzle_get_size (self);
			_tmp6_ = _tmp5_;
			if (!(_tmp4_ < (_tmp6_ * 2))) {
				break;
			}
			{
				gboolean _tmp7_;
				_vala_y = (guint) 0;
				_tmp7_ = TRUE;
				while (TRUE) {
					gboolean _tmp8_;
					guint _tmp10_;
					guint _tmp11_;
					guint _tmp12_;
					Tile** _tmp13_;
					gint _tmp13__length1;
					gint _tmp13__length2;
					guint _tmp14_;
					guint _tmp15_;
					Tile* _tmp16_;
					Tile* _tmp17_;
					_tmp8_ = _tmp7_;
					if (!_tmp8_) {
						guint _tmp9_;
						_tmp9_ = _vala_y;
						_vala_y = _tmp9_ + 1;
					}
					_tmp7_ = FALSE;
					_tmp10_ = _vala_y;
					_tmp11_ = puzzle_get_size (self);
					_tmp12_ = _tmp11_;
					if (!(_tmp10_ < _tmp12_)) {
						break;
					}
					_tmp13_ = self->priv->board;
					_tmp13__length1 = self->priv->board_length1;
					_tmp13__length2 = self->priv->board_length2;
					_tmp14_ = _vala_x;
					_tmp15_ = _vala_y;
					_tmp16_ = _tmp13_[(_tmp14_ * _tmp13__length2) + _tmp15_];
					_tmp17_ = tile;
					if (_tmp16_ == _tmp17_) {
						if (x) {
							*x = _vala_x;
						}
						if (y) {
							*y = _vala_y;
						}
						return;
					}
				}
			}
		}
	}
	if (x) {
		*x = _vala_x;
	}
	if (y) {
		*y = _vala_y;
	}
}
