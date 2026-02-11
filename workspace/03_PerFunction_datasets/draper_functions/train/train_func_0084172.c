shutdown_tree(void) {
    oid ccitt[1]           = { 0 };
    oid iso[1]             = { 1 };
    oid joint_ccitt_iso[1] = { 2 };

    DEBUGMSGTL(("agent_registry", "shut down tree\n"));

    remove_tree_entry(joint_ccitt_iso, 1);
    remove_tree_entry(iso, 1);
    remove_tree_entry(ccitt, 1);

}
