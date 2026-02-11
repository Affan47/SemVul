xmlCreateNewCatalog(xmlCatalogType type, xmlCatalogPrefer prefer) {
    xmlCatalogPtr ret;

    ret = (xmlCatalogPtr) xmlMalloc(sizeof(xmlCatalog));
    if (ret == NULL) {
        xmlCatalogErrMemory("allocating catalog");
        return(NULL);
    }
    memset(ret, 0, sizeof(xmlCatalog));
    ret->type = type;
    ret->catalNr = 0;
    ret->catalMax = XML_MAX_SGML_CATA_DEPTH;
    ret->prefer = prefer;
    if (ret->type == XML_SGML_CATALOG_TYPE)
        ret->sgml = xmlHashCreate(10);
    return(ret);
}
