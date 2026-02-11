to_xml_rec(xmlNodePtr pnode, struct tree *start,
                      const char *pathin) {
    int r;
    xmlNodePtr elem;

    elem = xmlNewChild(pnode, NULL, BAD_CAST "node", NULL);
    if (elem == NULL)
        goto error;
    r = to_xml_one(elem, start, pathin);
    if (r < 0)
        goto error;

    list_for_each(tree, start->children) {
        if (TREE_HIDDEN(tree))
            continue;
        r = to_xml_rec(elem, tree, NULL);
        if (r < 0)
            goto error;
    }

    return 0;
 error:
    return -1;
}
