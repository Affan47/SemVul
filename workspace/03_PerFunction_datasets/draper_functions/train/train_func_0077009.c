change_number_dlg_list(dlg_list_type *start) {
    dlg_list_type *p;
    dlg_type *dlg;
    int count = 0;

    for (p = start; p != NULL; p = p->next) {
	dlg = (dlg_type *)(p->cnt);
	dlg->no = count++;
    }
}
