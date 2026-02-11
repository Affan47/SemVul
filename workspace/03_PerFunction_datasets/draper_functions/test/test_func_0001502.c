game_finalize (Game* obj) {
	Game * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_GAME, Game);
	_map_unref0 (self->map);
	__g_list_free__tile_unref0_0 (self->tiles);
	_vala_array_destroy (self->hint_tiles, 2, (GDestroyNotify) tile_unref);
	_g_timer_destroy0 (self->priv->clock);
	_tile_unref0 (self->priv->_selected_tile);
}
