wimaxasncp_dict_free(wimaxasncp_dict_t *d) {
	wimaxasncp_dict_tlv_t *t, *tn;

#define FREE_NAMEANDOBJ(n) do { if(n->name) g_free(n->name); g_free(n); } while(0)

	for (t = d->tlvs; t; t = tn) {
		wimaxasncp_dict_enum_t *e, *en;
		tn = t->next;

		for (e = t->enums; e; e = en) {
			en = e->next;
			FREE_NAMEANDOBJ(e);
		}

		if (!t->description)  g_free(t->description);
		FREE_NAMEANDOBJ(t);
	}

	g_free(d);
}
