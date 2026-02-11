xmlSecCheckNodeName(const xmlNodePtr cur, const xmlChar *name, const xmlChar *ns) {
    xmlSecAssert2(cur != NULL, 0);

    return(xmlStrEqual(cur->name, name) &&
           xmlStrEqual(xmlSecGetNodeNsHref(cur), ns));
}
