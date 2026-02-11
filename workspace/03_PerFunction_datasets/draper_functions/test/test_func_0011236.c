remove_tree_entry (oid *name, size_t len) {

    netsnmp_subtree *sub = NULL;

    if ((sub = netsnmp_subtree_find(name, len, NULL, "")) == NULL) {
	return MIB_NO_SUCH_REGISTRATION;
    }

    return unregister_mib_context(name, len, sub->priority,
				  sub->range_subid, sub->range_ubound, "");

}
