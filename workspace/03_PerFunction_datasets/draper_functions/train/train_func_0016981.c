service_type_browser_callback(
    AVAHI_GCC_UNUSED AvahiSServiceTypeBrowser *b,
    AVAHI_GCC_UNUSED AvahiIfIndex interface,
    AVAHI_GCC_UNUSED AvahiProtocol protocol,
    AvahiBrowserEvent event,
    const char *service_type,
    const char *domain,
    AVAHI_GCC_UNUSED AvahiLookupResultFlags flags,
    AVAHI_GCC_UNUSED void * userdata) {

    struct ServiceType *st;
    GtkTreePath *path;
    GtkTreeIter iter;

    if (event != AVAHI_BROWSER_NEW)
        return;

    if (g_hash_table_lookup(service_type_hash_table, service_type))
        return;

    st = g_new(struct ServiceType, 1);
    st->service_type = g_strdup(service_type);
    st->services = NULL;

    gtk_tree_store_append(tree_store, &iter, NULL);
    gtk_tree_store_set(tree_store, &iter, 0, st->service_type, 1, "", 2, NULL, -1);

    path = gtk_tree_model_get_path(GTK_TREE_MODEL(tree_store), &iter);
    st->tree_ref = gtk_tree_row_reference_new(GTK_TREE_MODEL(tree_store), path);
    gtk_tree_path_free(path);

    g_hash_table_insert(service_type_hash_table, st->service_type, st);

    st->browser = avahi_s_service_browser_new(server, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, st->service_type, domain, 0, service_browser_callback, NULL);
}
