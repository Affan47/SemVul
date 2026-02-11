tree_write_tree_rek(GBDATA *gb_tree, AP_tree * THIS) {
    GB_ERROR error = NULL;
    if (!THIS->is_leaf) {
        error             = tree_write_tree_rek(gb_tree,THIS->leftson);
        if (!error) error = tree_write_tree_rek(gb_tree,THIS->rightson);

        if (!error) error = tree_write_float(gb_tree, THIS, THIS->gr.spread,          "spread",          1.0);
        if (!error) error = tree_write_float(gb_tree, THIS, THIS->gr.left_angle,      "left_angle",      0.0);
        if (!error) error = tree_write_float(gb_tree, THIS, THIS->gr.right_angle,     "right_angle",     0.0);
        if (!error) error = tree_write_byte (gb_tree, THIS, THIS->gr.left_linewidth,  "left_linewidth",  0);
        if (!error) error = tree_write_byte (gb_tree, THIS, THIS->gr.right_linewidth, "right_linewidth", 0);
        if (!error) error = tree_write_byte (gb_tree, THIS, THIS->gr.grouped,         "grouped",         0);
    }
    return error;
}
