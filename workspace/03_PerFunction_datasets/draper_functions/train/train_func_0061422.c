get_total_dlg_number(int mtg_id, int tlg_id) {
    mtg_type *mtg = search_mtg(localize_mtg_head, mtg_id);

    if (mtg != NULL) {
	tlg_type *tlg = search_tlg(mtg->tlg_list, tlg_id);
	if (tlg != NULL) {
	    tlg_list_type *list = tlg->dlg_list;
	    int count = 0;

	    while(list != NULL) {
		list = list->next;
		count++;
	    }
	    return count;
	}
    }
    return 0;
}
