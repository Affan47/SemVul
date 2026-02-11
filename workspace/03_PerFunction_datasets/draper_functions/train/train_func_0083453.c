_tpf_persona_store_contact_weak_notify_cb (TpfPersonaStore* self, GObject* obj) {
	GeeHashMap* _tmp0_ = NULL;
	TpContact* contact = NULL;
	GObject* _tmp1_ = NULL;
	TpContact* _tmp2_ = NULL;
	TpContact* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	TpfPersona* persona = NULL;
	GeeHashMap* _tmp5_ = NULL;
	TpContact* _tmp6_ = NULL;
	gpointer _tmp7_ = NULL;
	TpfPersona* _tmp8_ = NULL;
	TpfPersona* _tmp9_ = NULL;
	TpfPersona* _tmp10_ = NULL;
	gboolean _tmp11_ = FALSE;
	g_return_if_fail (self != NULL);
	g_return_if_fail (obj != NULL);
	_tmp0_ = self->priv->_contact_persona_map;
	if (_tmp0_ == NULL) {
		return;
	}
	_tmp1_ = obj;
	_tmp2_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp1_, tp_contact_get_type ()) ? ((TpContact*) _tmp1_) : NULL);
	contact = _tmp2_;
	_tmp3_ = contact;
	_tmp4_ = tp_contact_get_identifier (_tmp3_);
	g_debug ("tpf-persona-store.vala:1098: Weak notify for TpContact %s", _tmp4_);
	persona = NULL;
	_tmp5_ = self->priv->_contact_persona_map;
	_tmp6_ = contact;
	gee_abstract_map_unset ((GeeAbstractMap*) _tmp5_, _tmp6_, &_tmp7_);
	_g_object_unref0 (persona);
	persona = _tmp7_;
	_tmp8_ = persona;
	if (_tmp8_ == NULL) {
		_g_object_unref0 (persona);
		_g_object_unref0 (contact);
		return;
	}
	_tmp9_ = persona;
	_tpf_persona_contact_weak_notify (_tmp9_);
	_tmp10_ = persona;
	_tmp11_ = _tpf_persona_store_remove_persona (self, _tmp10_);
	if (_tmp11_) {
		FolksSmallSet* personas = NULL;
		FolksSmallSet* _tmp12_ = NULL;
		FolksSmallSet* _tmp13_ = NULL;
		TpfPersona* _tmp14_ = NULL;
		FolksSmallSet* _tmp15_ = NULL;
		g_warning ("tpf-persona-store.vala:1114: A TpContact part of the ContactList is di" \
"sposed");
		_tmp12_ = folks_small_set_new (TPF_TYPE_PERSONA, (GBoxedCopyFunc) g_object_ref, g_object_unref, NULL, NULL, NULL, NULL, NULL, NULL);
		personas = _tmp12_;
		_tmp13_ = personas;
		_tmp14_ = persona;
		gee_abstract_collection_add ((GeeAbstractCollection*) _tmp13_, _tmp14_);
		_tmp15_ = personas;
		_folks_persona_store_emit_personas_changed ((FolksPersonaStore*) self, NULL, (GeeSet*) _tmp15_, NULL, NULL, FOLKS_GROUP_DETAILS_CHANGE_REASON_NONE);
		_g_object_unref0 (personas);
	}
	_g_object_unref0 (persona);
	_g_object_unref0 (contact);
}
