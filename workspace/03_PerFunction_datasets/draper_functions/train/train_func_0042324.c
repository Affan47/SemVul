osinfo_loader_deployment(OsinfoLoader *loader,
                                     xmlXPathContextPtr ctxt,
                                     xmlNodePtr root,
                                     GError **err)
{
    gchar *id = (gchar *)xmlGetProp(root, BAD_CAST "id");
    if (!id) {
        OSINFO_ERROR(err, _("Missing deployment id property"));
        return;
    }

    gchar *osid = osinfo_loader_string("string(./os/@id)", ctxt, err);
    if (!osid && 0) {
        OSINFO_ERROR(err, _("Missing deployment os id property"));
        xmlFree(id);
        return;
    }
    OsinfoOs *os = osinfo_loader_get_os(loader, osid);
    g_free(osid);

    gchar *platformid = osinfo_loader_string("string(./platform/@id)", ctxt, err);
    if (!platformid) {
        OSINFO_ERROR(err, _("Missing deployment platform id property"));
        xmlFree(id);
        return;
    }
    OsinfoPlatform *platform = osinfo_loader_get_platform(loader, platformid);
    g_free(platformid);

    OsinfoDeployment *deployment = osinfo_deployment_new(id, os, platform);
    xmlFree(id);

    osinfo_loader_entity(loader, OSINFO_ENTITY(deployment), NULL, ctxt, root, err);
    if (error_is_set(err)) {
        g_object_unref(G_OBJECT(deployment));
        return;
    }

    osinfo_loader_device_link(loader, OSINFO_ENTITY(deployment),
                              "./devices/device", ctxt, root, err);
    if (error_is_set(err)) {
        g_object_unref(G_OBJECT(deployment));
        return;
    }

    osinfo_db_add_deployment(loader->priv->db, deployment);
}
