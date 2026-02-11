change_number_tlg_list(tlg_list_type *start) {
    tlg_list_type *p;
    tlg_type *tlg;
    int count = 0;

    for (p = start; p != NULL; p = p->next) {
	tlg = (tlg_type *)(p->cnt);
	change_number_dlg_list(tlg->dlg_list);
	tlg->no = count++;
    }
}
