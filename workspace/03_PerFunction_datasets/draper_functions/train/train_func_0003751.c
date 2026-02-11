add_pkg(gpointer data, gpointer user_data) {
    PkgNode *pkg = (PkgNode *)data;
    GHashTable *ht_packages = (GHashTable *)(((gpointer *)user_data)[0]);
    HostNode *node = (HostNode *)(((gpointer *)user_data)[1]);

    ASSERT_TYPE(pkg, T_PKGNODE);
    ASSERT_TYPE(node, T_HOSTNODE);

    if (!test_pkg(pkg))
	return;

    gchar *v;
    if(((pkg->flag & HOST_STATUS_PKGUPDATE) ||
        (pkg->flag & HOST_STATUS_PKGKEPTBACK)) &&
        (pkg->data))
     v = pkg->data;
    else
     v = pkg->version;

    if(!v)
     return;


    GList *l_versions = g_hash_table_lookup(ht_packages, pkg->package);

    Version _v;
#ifndef NDEBUG
    _v._type = T_VERSION;
#endif
    _v.version = v;


    Version *vers = NULL;
    GList *l_v = g_list_find_custom(l_versions, &_v, cmp_vers);
    if (l_v) {
	vers = (Version *)l_v->data;
	ASSERT_TYPE(vers, T_VERSION);
    }

    if(!vers) {
	vers = g_malloc(sizeof(Version));
#ifndef NDEBUG
	vers->_type = T_VERSION;
#endif
	vers->version = strdup(v);
	vers->ts_first = node->last_upd;
	vers->nodes = NULL;

	l_versions = g_list_prepend(l_versions, vers);
	g_hash_table_insert(ht_packages, g_strdup(pkg->package), l_versions);
    }
    else if (vers->ts_first > node->last_upd) {
	vers->ts_first = node->last_upd;
    }

    vers->nodes = g_list_prepend(vers->nodes, node);
}
