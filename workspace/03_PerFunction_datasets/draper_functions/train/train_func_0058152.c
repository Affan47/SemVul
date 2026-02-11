osinfo_loader_resources(OsinfoLoader *loader,
                                                xmlXPathContextPtr ctxt,
                                                xmlNodePtr root,
                                                const gchar *id,
                                                const gchar *name,
                                                GError **err)
{
    xmlNodePtr *nodes = NULL;
    OsinfoResources *resources = NULL;
    guint i;

    gchar *arch = (gchar *)xmlGetProp(root, BAD_CAST "arch");
    gchar *node_path = g_strjoin("/", ".", name, "*", NULL);
    gint nnodes = osinfo_loader_nodeset(node_path, ctxt, &nodes, err);
    g_free(node_path);
    if (error_is_set(err) || nnodes < 1)
        goto EXIT;

    resources = osinfo_resources_new(id, arch);

    for (i = 0 ; i < nnodes ; i++) {
        if (!nodes[i]->children ||
            nodes[i]->children->type != XML_TEXT_NODE ||
            (strcmp((const gchar *)nodes[i]->name,
                    OSINFO_RESOURCES_PROP_CPU) != 0 &&
             strcmp((const gchar *)nodes[i]->name,
                    OSINFO_RESOURCES_PROP_N_CPUS) != 0 &&
             strcmp((const gchar *)nodes[i]->name,
                    OSINFO_RESOURCES_PROP_RAM) != 0 &&
             strcmp((const gchar *)nodes[i]->name,
                    OSINFO_RESOURCES_PROP_STORAGE) != 0))
            continue;

        osinfo_entity_set_param(OSINFO_ENTITY(resources),
                                (const gchar *)nodes[i]->name,
                                (const gchar *)nodes[i]->children->content);
    }

EXIT:
    g_free(nodes);
    xmlFree(arch);

    return resources;
}
