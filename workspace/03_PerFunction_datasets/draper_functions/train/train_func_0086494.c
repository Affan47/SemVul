xmlSecFindChild(const xmlNodePtr parent, const xmlChar *name, const xmlChar *ns) {
    xmlNodePtr cur;

    xmlSecAssert2(parent != NULL, NULL);
    xmlSecAssert2(name != NULL, NULL);

    cur = parent->children;
    while(cur != NULL) {
        if(cur->type == XML_ELEMENT_NODE) {
            if(xmlSecCheckNodeName(cur, name, ns)) {
                return(cur);
            }
        }
        cur = cur->next;
    }
    return(NULL);
}
