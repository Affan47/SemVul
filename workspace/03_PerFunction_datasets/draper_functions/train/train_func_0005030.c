gf_smil_timing_reset_time_list(GF_List *times)
{
	GF_DOMEventTarget *evt;
	u32 i;
	for (i=0; i<gf_list_count(times); i++) {
		SMIL_Time *t = gf_list_get(times, i);
		if (!t->listener) continue;


		evt = t->listener->sgprivate->UserPrivate;
		t->listener->sgprivate->UserPrivate = NULL;
		gf_dom_listener_del(t->listener, evt);


		gf_node_unregister(t->listener, NULL);
		t->listener = NULL;
	}
}
