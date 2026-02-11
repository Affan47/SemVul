osinfo_install_script_generate_config_xml(OsinfoInstallScript *script,
                                                           OsinfoOs *os,
                                                           OsinfoInstallConfig *config,
                                                           const gchar *node_name,
                                                           GError **error)
{
    xmlDocPtr doc = xmlNewDoc((xmlChar *)"1.0");
    xmlNodePtr root;
    xmlNodePtr node;

    root = xmlNewDocNode(NULL,
                         NULL,
                         (xmlChar*)node_name,
                         NULL);
    xmlDocSetRootElement(doc, root);

    if (!(node = osinfo_install_script_generate_entity_xml(script,
                                                           OSINFO_ENTITY(script),
                                                           "script",
                                                           error)))
        goto error;
    if (!(xmlAddChild(root, node))) {
        xmlErrorPtr err = xmlGetLastError();
        g_set_error(error, 0, 0, _("Unable to set XML root '%s'"), err ? err->message : "");
        goto error;
    }

    if (!(node = osinfo_install_script_generate_entity_xml(script,
                                                           OSINFO_ENTITY(os),
                                                           "os",
                                                           error)))
        goto error;
    if (!(xmlAddChild(root, node))) {
        xmlErrorPtr err = xmlGetLastError();
        g_set_error(error, 0, 0, _("Unable to set XML root '%s'"), err ? err->message : "");
        goto error;
    }

    if (!(node = osinfo_install_script_generate_entity_xml(script,
                                                           OSINFO_ENTITY(config),
                                                           "config",
                                                           error)))
        goto error;
    if (!(xmlAddChild(root, node))) {
        xmlErrorPtr err = xmlGetLastError();
        g_set_error(error, 0, 0, _("Unable to set XML root '%s'"), err ? err->message : "");
        goto error;
    }

    return doc;

 error:
    xmlFreeDoc(doc);
    doc = NULL;
    return NULL;
}
