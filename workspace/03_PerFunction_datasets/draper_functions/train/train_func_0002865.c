_tpf_persona_contact_notify_presence_type (TpfPersona* self) {
	TpContact* contact = NULL;
	TpContact* _tmp0_ = NULL;
	TpContact* _tmp1_ = NULL;
	TpConnectionPresenceType _tmp2_ = 0;
	FolksPresenceType _tmp3_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->_contact;
	_tmp1_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_CAST (_tmp0_, tp_contact_get_type (), TpContact));
	contact = _tmp1_;
	_vala_assert (contact != NULL, "contact != null");
	_tmp2_ = tp_contact_get_presence_type (contact);
	_tmp3_ = _tpf_persona_folks_presence_type_from_tp (_tmp2_);
	folks_presence_details_set_presence_type ((FolksPresenceDetails*) self, _tmp3_);
	_g_object_unref0 (contact);
}
