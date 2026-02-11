change_array_entry_dtu(Dtu_trans_group *dtu_head, int src_entry, int dest_entry)
{
    Dtu_trans_group *dtu;
    Dtu_entry_table *dtu_etbl;
    for (dtu = dtu_head; dtu != NULL; dtu = dtu->next) {
        for (dtu_etbl = dtu->entry_head; dtu_etbl != NULL; dtu_etbl = dtu_etbl->next) {
            if (dtu_etbl->source->opt->entry == src_entry) {
                dtu_etbl->source->opt->entry = dest_entry;
	    }
            if (dtu_etbl->destination->opt->entry == src_entry) {
                dtu_etbl->destination->opt->entry = dest_entry;
	    }
	}
    }
}
