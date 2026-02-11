op_indexer_destroy (Slapi_PBlock* pb)
{
    auto indexer_t* ix = op_indexer_get (pb);
    LDAPDebug (LDAP_DEBUG_FILTER, "op_indexer_destroy(%p)\n", (void*)ix, 0, 0);
    if (ix != NULL) {
	indexer_free (ix);
    }
    return 0;
}
