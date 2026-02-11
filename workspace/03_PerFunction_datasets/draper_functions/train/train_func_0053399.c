select_array_du_slot_type(Block *b, Array_def_use_table_semnode *local_du,
                          const int slot_type)
{
    Array_def_use_table_semnode *apt, dummy, *rpt, *next, *du;
    Template *templ;
    dummy.next = NULL;
    rpt = &dummy;
    for (apt = local_du; apt != NULL; apt = next) {
        next = apt->next;
        templ = get_template_by_array_entry(b->template_list_set_list,
                                            b->module, apt->entry);
        du = copy_array_def_use_table_semnode(apt);
        du = max_range_array_def_use_table_semnode(du, NULL);
        if ((templ != NULL) && (slot_type == templ->kind)) {
            rpt->next = apt;
            rpt = rpt->next;
            rpt->next = NULL;
        } else {
            free_array_def_use_table_semnode(apt);
        }
        free_array_def_use_table_semnode(du);
    }

    return dummy.next;

}
