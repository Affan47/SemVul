_enabled_comparator(GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer user_data)
{
    GncSxListTreeModelAdapter *adapter = GNC_SX_LIST_TREE_MODEL_ADAPTER(user_data);
    GncSxInstances *a_inst, *b_inst;

    a_inst = gsltma_get_sx_instances_from_orig_iter(adapter, a);
    b_inst = gsltma_get_sx_instances_from_orig_iter(adapter, b);

    if (xaccSchedXactionGetEnabled(a_inst->sx) && !xaccSchedXactionGetEnabled(b_inst->sx)) return 1;
    if (!xaccSchedXactionGetEnabled(a_inst->sx) && xaccSchedXactionGetEnabled(b_inst->sx)) return -1;
    return 0;
}
