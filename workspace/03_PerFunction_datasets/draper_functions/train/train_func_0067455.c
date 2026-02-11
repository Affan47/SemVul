_edsf_persona_get_property_from_contact (GType t_type, GBoxedCopyFunc t_dup_func, GDestroyNotify t_destroy_func, EContact* contact, const gchar* prop_name) {
	gpointer result = NULL;
	gpointer prop_value = NULL;
	EContact* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	EContactField _tmp2_ = 0;
	gpointer _tmp3_ = NULL;
	g_return_val_if_fail (contact != NULL, NULL);
	g_return_val_if_fail (prop_name != NULL, NULL);
	prop_value = NULL;
	_tmp0_ = contact;
	_tmp1_ = prop_name;
	_tmp2_ = e_contact_field_id (_tmp1_);
	_tmp3_ = e_contact_get (_tmp0_, _tmp2_);
	_t_destroy_func0 (prop_value);
	prop_value = _tmp3_;
	result = prop_value;
	return result;
}
