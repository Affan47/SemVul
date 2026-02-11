computer_player_calculate_heuristic (ComputerPlayer* self, Game* g, Strategy strategy) {
	gint result = 0;
	Game* _tmp0_;
	gint _tmp1_;
	gint _tmp2_;
	Game* _tmp3_;
	gint _tmp4_;
	gint _tmp5_;
	gint tile_difference;
	Game* _tmp6_;
	Player _tmp7_;
	Strategy _tmp9_;
	g_return_val_if_fail (self != NULL, 0);
	g_return_val_if_fail (g != NULL, 0);
	_tmp0_ = g;
	_tmp1_ = game_get_n_dark_tiles (_tmp0_);
	_tmp2_ = _tmp1_;
	_tmp3_ = g;
	_tmp4_ = game_get_n_light_tiles (_tmp3_);
	_tmp5_ = _tmp4_;
	tile_difference = _tmp2_ - _tmp5_;
	_tmp6_ = g;
	_tmp7_ = _tmp6_->current_color;
	if (_tmp7_ == PLAYER_DARK) {
		gint _tmp8_;
		_tmp8_ = tile_difference;
		tile_difference = -_tmp8_;
	}
	_tmp9_ = strategy;
	switch (_tmp9_) {
		case STRATEGY_PERFECT:
		{
			result = tile_difference;
			return result;
		}
		case STRATEGY_VICTORY:
		{
			gint _tmp10_;
			gint _tmp11_ = 0;
			_tmp10_ = tile_difference;
			_tmp11_ = CLAMP (_tmp10_, -1, 1);
			result = _tmp11_;
			return result;
		}
		default:
		{
			gint _tmp12_;
			gint _tmp13_ = 0;
			gint _tmp14_ = 0;
			_tmp12_ = tile_difference;
			_tmp13_ = computer_player_around (self);
			_tmp14_ = computer_player_eval_heuristic (self);
			result = (_tmp12_ + _tmp13_) + _tmp14_;
			return result;
		}
	}
}
