profile_update_root_action_state (Profile* self) {
	GSimpleAction* _tmp0_ = NULL;
	GVariant* _tmp1_ = NULL;
	GVariant* _tmp2_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->root_action;
	_tmp1_ = profile_action_state_for_root (self);
	_tmp2_ = _tmp1_;
	g_simple_action_set_state (_tmp0_, _tmp2_);
	_g_variant_unref0 (_tmp2_);
}
