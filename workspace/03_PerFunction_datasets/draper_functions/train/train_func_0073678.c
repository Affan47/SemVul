NT_alltree_remove_leafs(AW_window *, AW_CL cl_mode, AW_CL cl_gb_main) {
    GBDATA               *gb_main = (GBDATA*)cl_gb_main;
    GBT_TREE_REMOVE_TYPE  mode    = (GBT_TREE_REMOVE_TYPE)cl_mode;

    GB_transaction ta(gb_main);

    int    treeCount;
    char **tree_names = GBT_get_tree_names_and_count(gb_main, &treeCount);

    if (tree_names) {
        aw_openstatus("Deleting from trees");
        GB_HASH *species_hash = GBT_create_species_hash(gb_main);

        for (int t = 0; t<treeCount; t++) {
            GB_ERROR  error = 0;
            aw_status(t/double(treeCount));
            aw_status(tree_names[t]);
            GBT_TREE *tree = GBT_read_tree(gb_main, tree_names[t], -sizeof(GBT_TREE));
            if (!tree) {
                aw_message(GBS_global_string("Can't load tree '%s' - skipped", tree_names[t]));
            }
            else {
                int removed        = 0;
                int groups_removed = 0;

                tree = GBT_remove_leafs(tree, mode, species_hash, &removed, &groups_removed);

                gb_assert(removed >= groups_removed);

                if (!tree) {
                    aw_message(GBS_global_string("'%s' would disappear. Please delete tree manually.", tree_names[t]));
                }
                else {
                    if (removed>0) {
                        error = GBT_write_tree(gb_main, 0, tree_names[t], tree);
                        if (groups_removed>0) {
                            aw_message(GBS_global_string("Removed %i species and %i groups from '%s'", removed, groups_removed, tree_names[t]));
                        }
                        else {
                            aw_message(GBS_global_string("Removed %i species from '%s'", removed, tree_names[t]));
                        }
                    }
                    GBT_delete_tree(tree);
                }
            }
            if (error) aw_message(error);
        }
        aw_status(1.0);

        GBT_free_names(tree_names);
        GBS_free_hash(species_hash);
        aw_closestatus();
    }
}
