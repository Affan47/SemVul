gf_m2ts_mux_stream_del(GF_M2TS_Mux_Stream *st)
{
	while (st->tables) {
		GF_M2TS_Mux_Table *tab = st->tables->next;
		while (st->tables->section) {
			GF_M2TS_Mux_Section *sec = st->tables->section->next;
			gf_free(st->tables->section->data);
			gf_free(st->tables->section);
			st->tables->section = sec;
		}
		gf_free(st->tables);
		st->tables = tab;
	}
	while (st->pck_first) {
		GF_M2TS_Packet *curr_pck = st->pck_first;
		st->pck_first = curr_pck->next;
		gf_free(curr_pck->data);
		gf_free(curr_pck);
	}
	if (st->curr_pck.data) gf_free(st->curr_pck.data);
	if (st->mx) gf_mx_del(st->mx);
	gf_free(st);
}
