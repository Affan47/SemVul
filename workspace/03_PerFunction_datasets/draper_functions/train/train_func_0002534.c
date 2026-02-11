ya_select_localize_common_region_callee(Module_table *caller, Block *sb)
{
    Module_table *callee = sb_callee(sb);
    module_kind rkind = caller->kind;
    module_kind ekind = callee->kind;
    int rentry = caller->entry;
    int eentry = callee->entry;
    int rmax = get_max_region_entry(region_head);
    List *ehead, *li, *rhead;
    Node_offset_size *npt;
    int i;

    for (i = 0; i <= rmax; i++) {
        ehead = (ekind == MODULE_FUNC)
            ? func_nolocal_node[eentry][i]
            : subr_nolocal_node[eentry][i];
        for (li = ehead; li != NULL; li = li->next) {
            Node_offset_size *ref = li->data;
            rhead = (rkind == MODULE_FUNC)
                ? func_local_node[rentry][i]
                : subr_local_node[rentry][i];
            if ((npt = list_lookup(rhead, cmp_node_offset_size,
                                   ref)) != NULL) {
                if (rkind == MODULE_FUNC) {
                    func_local_node[rentry][i]
                        = list_remove(func_local_node[rentry][i], npt);
                    func_nolocal_node[rentry][i]
                        = list_append(func_nolocal_node[rentry][i], npt);
                } else {
                    subr_local_node[rentry][i]
                        = list_remove(subr_local_node[rentry][i], npt);
                    subr_nolocal_node[rentry][i]
                        = list_append(subr_nolocal_node[rentry][i], npt);
                }
            }
        }
    }
}
