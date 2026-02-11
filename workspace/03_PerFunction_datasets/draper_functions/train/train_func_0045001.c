set_templ_array_rev_for_common(IntSet callee_templ, IntSet caller_templ,
                               Array_table *atblee_head, Module_table *caller)
{
    Array_table *atbl;
    Array_table *caller_atbl;
    Common_table *caller_tbl;
    Common_node *caller_node;
    for (atbl = atblee_head; atbl != NULL; atbl = atbl->next) {
        if (atbl->node != NULL) {
            if (in_IntSet(callee_templ, atbl->entry)) {
                caller_tbl = search_common_table(caller, atbl->node->region);
                caller_node = search_common_node(caller_tbl, atbl->node);
                caller_atbl = search_array_table_by_node(caller->array_head,
                                                         caller_node);
                add1_IntSet(caller_templ, caller_atbl->entry);
            }
        }
    }
}
