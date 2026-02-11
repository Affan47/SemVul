PARS_generate_tree(AW_root *root) {
    AWT_graphic_parsimony *apdt  = new AWT_graphic_parsimony(root,GLOBAL_gb_main);
    AP_tree_nlen          *aptnl = new AP_tree_nlen(0);

    apdt->init((AP_tree *)aptnl);
    ap_main->tree_root = &apdt->tree_root;

    delete aptnl;
    return apdt;
}
