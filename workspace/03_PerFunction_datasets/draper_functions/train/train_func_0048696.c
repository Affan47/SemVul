NT_remove_bootstrap(AW_window*, AW_CL cl_ntw, AW_CL)
{
    AWT_canvas     *ntw = (AWT_canvas*)cl_ntw;
    GB_transaction  gb_dummy(ntw->gb_main);

    AWT_TREE(ntw)->check_update(ntw->gb_main);

    AP_tree *tree_root = AWT_TREE(ntw)->tree_root;
    if (tree_root) {
        tree_root->remove_bootstrap(ntw->gb_main);
        tree_root->compute_tree(ntw->gb_main);
        nt_save_changed_tree(ntw);
    }
}
