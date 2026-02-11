mark_species_in_tree(AP_tree *at, int mark_mode) {


    if (!at) return;

    GB_transaction dummy(tree_static->gb_species_data);
    if (at->is_leaf) {
        if(at->gb_node) {
            switch (mark_mode) {
                case 0: GB_write_flag(at->gb_node, 0); break;
                case 1: GB_write_flag(at->gb_node, 1); break;
                case 2: GB_write_flag(at->gb_node, !GB_read_flag(at->gb_node)); break;
                default : awt_assert(0);
            }
        }
    }

    mark_species_in_tree(at->leftson, mark_mode);
    mark_species_in_tree(at->rightson, mark_mode);
}
