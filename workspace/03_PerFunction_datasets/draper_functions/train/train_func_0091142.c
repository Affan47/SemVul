create_common_node (Module_table *current_mpt,
                               int max_region_entry)
{
    Var_table *vpt;
    Array_table *apt;
    int sum_size = 0;

    for (vpt = current_mpt->var_head; vpt; vpt = vpt->next) {
        if (vpt->save == FALSE || vpt->node != NULL) continue;
        vpt->node = alloc_common_node();
        vpt->save = FALSE;
        sum_size += set_common_node_parameter (vpt->node,
                                               KIND_VAR,
                                               vpt->type,
                                               vpt,
                                               NULL,
                                               max_region_entry);
    }

    for (apt = current_mpt->array_head; apt; apt = apt->next) {
        if (apt->save == FALSE || apt->node != NULL) continue;
        apt->node = alloc_common_node();
        apt->save = FALSE;
        sum_size += set_common_node_parameter (apt->node,
                                               KIND_ARRAY,
                                               apt->type,
                                               NULL,
                                               apt,
                                               max_region_entry);
    }

    return (sum_size);
}
