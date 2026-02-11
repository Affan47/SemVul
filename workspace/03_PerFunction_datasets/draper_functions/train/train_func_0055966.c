command_show_listeners(client_t *client, source_t *source,
    int response)
{
    xmlDocPtr doc;
    xmlNodePtr node, srcnode, listenernode;
    avl_node *client_node;
    client_t *current;
    char buf[22];
    const char *userAgent = NULL;
    time_t now = time(NULL);

    doc = xmlNewDoc (XMLSTR("1.0"));
    node = xmlNewDocNode(doc, NULL, XMLSTR("icestats"), NULL);
    srcnode = xmlNewChild(node, NULL, XMLSTR("source"), NULL);
    xmlSetProp(srcnode, XMLSTR("mount"), XMLSTR(source->mount));
    xmlDocSetRootElement(doc, node);

    memset(buf, '\000', sizeof(buf));
    snprintf (buf, sizeof(buf), "%lu", source->listeners);
    xmlNewChild(srcnode, NULL, XMLSTR("Listeners"), XMLSTR(buf));

    avl_tree_rlock(source->client_tree);

    client_node = avl_get_first(source->client_tree);
    while(client_node) {
        current = (client_t *)client_node->key;
        listenernode = xmlNewChild(srcnode, NULL, XMLSTR("listener"), NULL);
        xmlNewChild(listenernode, NULL, XMLSTR("IP"), XMLSTR(current->con->ip));
        userAgent = httpp_getvar(current->parser, "user-agent");
        if (userAgent) {
            xmlNewChild(listenernode, NULL, XMLSTR("UserAgent"), XMLSTR(userAgent));
        }
        else {
            xmlNewChild(listenernode, NULL, XMLSTR("UserAgent"), XMLSTR("Unknown"));
        }
        memset(buf, '\000', sizeof(buf));
        snprintf(buf, sizeof(buf), "%lu", (unsigned long)(now - current->con->con_time));
        xmlNewChild(listenernode, NULL, XMLSTR("Connected"), XMLSTR(buf));
        memset(buf, '\000', sizeof(buf));
        snprintf(buf, sizeof(buf)-1, "%lu", current->con->id);
        xmlNewChild(listenernode, NULL, XMLSTR("ID"), XMLSTR(buf));
        if (current->username) {
            xmlNewChild(listenernode, NULL, XMLSTR("username"), XMLSTR(current->username));
        }
        client_node = avl_get_next(client_node);
    }

    avl_tree_unlock(source->client_tree);
    admin_send_response(doc, client, response,
        LISTCLIENTS_TRANSFORMED_REQUEST);
    xmlFreeDoc(doc);
}
