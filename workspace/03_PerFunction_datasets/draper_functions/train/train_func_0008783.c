lad_process_directive(Module_table *module_head)
{
    List *list;
    List *li;

    list = make_lad_list(module_head);

    if (list == NULL)
        return FALSE;

    for (li = list; li != NULL; li = li->next) {
        sLadTlg *tlg = sLadTlg_create(li->data);
        sLadTlg_apply(tlg);
        sLadTlg_destroy(tlg);
    }

    list_free(list);
    return TRUE;
}
