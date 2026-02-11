bfa_itnim_iotov_delete(struct bfa_itnim_s *itnim)
{
	bfa_boolean_t pathtov_active = BFA_FALSE;

	if (itnim->iotov_active)
		pathtov_active = BFA_TRUE;

	bfa_itnim_iotov_stop(itnim);
	if (pathtov_active)
		bfa_cb_itnim_tov_begin(itnim->ditn);
	bfa_itnim_iotov_cleanup(itnim);
	if (pathtov_active)
		bfa_cb_itnim_tov(itnim->ditn);
}
