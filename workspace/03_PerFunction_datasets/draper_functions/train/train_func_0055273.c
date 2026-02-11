test_isleaf(std_btree tree)
{
    std_btree_iterator i = std_btree_root(tree);

    debug("Test starting: Isleaf\n");

    if (std_btree_isleaf(i)) {
        debug("Isleaf returned true when it's clearly false\n");
        return 1;
    }


    i = std_btree_child(i, STD_BTREE_RIGHT);
    i = std_btree_child(i, STD_BTREE_LEFT);

    if (!std_btree_isleaf(i)) {
        debug("Isleaf returned false when it's clearly true\n");
        return 2;
    }

    debug("Test complete: Isleaf\n");
    return 0;
}
