jump(AP_tree *at, const char *name)
{
    if (sort_is_list_style(tree_sort)) return;

    at = search(at,name);
    if(!at) return;
    if (tree_sort == AP_TREE_NORMAL) {
        tree_root_display = tree_root;
    }else{
        while (at->father &&
               at->gr.view_sum<15 &&
               0 == at->gr.grouped)
        {
            at = at->father;
        }
        tree_root_display = at;
    }
}
