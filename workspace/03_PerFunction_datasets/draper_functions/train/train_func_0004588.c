admin_build_sourcelist (const char *mount)
{
    avl_node *node;
    source_t *source;
    xmlNodePtr xmlnode, srcnode;
    xmlDocPtr doc;
    char buf[22];
    time_t now = time(NULL);

    doc = xmlNewDoc (XMLSTR("1.0"));
    xmlnode = xmlNewDocNode (doc, NULL, XMLSTR("icestats"), NULL);
    xmlDocSetRootElement(doc, xmlnode);

    if (mount) {
        xmlNewChild (xmlnode, NULL, XMLSTR("current_source"), XMLSTR(mount));
    }

    node = avl_get_first(global.source_tree);
    while(node) {
        source = (source_t *)node->key;
        if (mount && strcmp (mount, source->mount) == 0)
        {
            node = avl_get_next (node);
            continue;
        }

        if (source->running || source->on_demand)
        {
            ice_config_t *config;
            mount_proxy *mountinfo;

            srcnode = xmlNewChild(xmlnode, NULL, XMLSTR("source"), NULL);
            xmlSetProp(srcnode, XMLSTR("mount"), XMLSTR(source->mount));

            xmlNewChild(srcnode, NULL, XMLSTR("fallback"),
                    (source->fallback_mount != NULL)?
                    XMLSTR(source->fallback_mount):XMLSTR(""));
            snprintf (buf, sizeof(buf), "%lu", source->listeners);
            xmlNewChild(srcnode, NULL, XMLSTR("listeners"), XMLSTR(buf));

            config = config_get_config();
            mountinfo = config_find_mount (config, source->mount);
            if (mountinfo && mountinfo->auth)
            {
                xmlNewChild(srcnode, NULL, XMLSTR("authenticator"),
                        XMLSTR(mountinfo->auth->type));
            }
            config_release_config();

            if (source->running)
            {
                if (source->client)
                {
                    snprintf (buf, sizeof(buf), "%lu",
                            (unsigned long)(now - source->con->con_time));
                    xmlNewChild (srcnode, NULL, XMLSTR("Connected"), XMLSTR(buf));
                }
                xmlNewChild (srcnode, NULL, XMLSTR("content-type"),
                        XMLSTR(source->format->contenttype));
            }
        }
        node = avl_get_next(node);
    }
    return(doc);
}
