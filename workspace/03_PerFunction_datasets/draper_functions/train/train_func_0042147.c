chess_scene_animate_cb (ChessScene* self) {
	gboolean result = FALSE;
	gdouble _tmp0_;
	gdouble old_time;
	GTimer* _tmp1_;
	gdouble _tmp2_ = 0.0;
	gdouble _tmp3_;
	gdouble _tmp4_;
	gdouble timestep;
	gint animate_count;
	GList* _tmp5_;
	gint _tmp11_;
	gboolean _tmp12_;
	ChessGame* _tmp13_;
	ChessGame* _tmp14_;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->priv->animation_time;
	old_time = _tmp0_;
	_tmp1_ = self->priv->animation_timer;
	_tmp2_ = g_timer_elapsed (_tmp1_, NULL);
	self->priv->animation_time = _tmp2_;
	_tmp3_ = self->priv->animation_time;
	_tmp4_ = old_time;
	timestep = _tmp3_ - _tmp4_;
	animate_count = 0;
	_tmp5_ = self->pieces;
	{
		GList* model_collection = NULL;
		GList* model_it = NULL;
		model_collection = _tmp5_;
		for (model_it = model_collection; model_it != NULL; model_it = model_it->next) {
			ChessModel* _tmp6_;
			ChessModel* model = NULL;
			_tmp6_ = _chess_model_ref0 ((ChessModel*) model_it->data);
			model = _tmp6_;
			{
				ChessModel* _tmp7_;
				gdouble _tmp8_;
				gboolean _tmp9_ = FALSE;
				_tmp7_ = model;
				_tmp8_ = timestep;
				_tmp9_ = chess_model_animate (_tmp7_, _tmp8_);
				if (_tmp9_) {
					gint _tmp10_;
					_tmp10_ = animate_count;
					animate_count = _tmp10_ + 1;
				}
				_chess_model_unref0 (model);
			}
		}
	}
	_tmp11_ = animate_count;
	self->animating = _tmp11_ > 0;
	g_signal_emit_by_name (self, "changed");
	_tmp12_ = self->animating;
	if (_tmp12_) {
		result = TRUE;
		return result;
	}
	self->animating = FALSE;
	_tmp13_ = chess_scene_get_game (self);
	_tmp14_ = _tmp13_;
	chess_game_remove_hold (_tmp14_);
	result = FALSE;
	return result;
}
