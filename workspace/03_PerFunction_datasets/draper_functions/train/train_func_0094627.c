_edsf_persona_store_copy_contacts_ids (EdsfPersonaStore* self, GList* contacts_ids) {
	GeeLinkedList* result = NULL;
	GeeLinkedList* copy = NULL;
	GeeLinkedList* _tmp0_ = NULL;
	GList* _tmp1_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = gee_linked_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL, NULL, NULL);
	copy = _tmp0_;
	_tmp1_ = contacts_ids;
	{
		GList* s_collection = NULL;
		GList* s_it = NULL;
		s_collection = _tmp1_;
		for (s_it = s_collection; s_it != NULL; s_it = s_it->next) {
			const gchar* s = NULL;
			s = (const gchar*) s_it->data;
			{
				GeeLinkedList* _tmp2_ = NULL;
				const gchar* _tmp3_ = NULL;
				_tmp2_ = copy;
				_tmp3_ = s;
				gee_abstract_collection_add ((GeeAbstractCollection*) _tmp2_, _tmp3_);
			}
		}
	}
	result = copy;
	return result;
}
