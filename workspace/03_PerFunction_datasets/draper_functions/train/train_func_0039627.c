gen_dlg_list_table(Block *block,
					  int    dlg_tag)
{
    Block          *bpt;
    Dlg_list_table *dlgpt = NULL;

    bpt = block;
    if (bpt != NULL) {
	dlgpt = alloc_dlg_list_table();
	if (dlgpt != NULL) {
	    dlgpt->mtg_id = bpt->outer->hmdf->mtg_id;
	    dlgpt->mt_no  = bpt->no;
            dlgpt->tlg_no = bpt->tlg_tag;
	    dlgpt->dlg_no = dlg_tag;
	}
    }

    return dlgpt;
}
