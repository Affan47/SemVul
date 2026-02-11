computer_player_construct (GType object_type, Game* game, gint level) {
	ComputerPlayer* self = NULL;
	Game* _tmp0_;
	Game* _tmp1_;
	gint _tmp2_;
	g_return_val_if_fail (game != NULL, NULL);
	self = (ComputerPlayer*) g_type_create_instance (object_type);
	_tmp0_ = game;
	_tmp1_ = _game_ref0 (_tmp0_);
	_game_unref0 (self->priv->game);
	self->priv->game = _tmp1_;
	_tmp2_ = level;
	self->priv->level = _tmp2_;
	return self;
}
