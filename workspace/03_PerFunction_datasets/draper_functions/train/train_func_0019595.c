xmlSchemaAddElement(xmlSchemaParserCtxtPtr ctxt,
                    const xmlChar * name, const xmlChar * nsName,
                    xmlNodePtr node, int topLevel)
{
    xmlSchemaElementPtr ret = NULL;

    if ((ctxt == NULL) || (name == NULL))
        return (NULL);

    ret = (xmlSchemaElementPtr) xmlMalloc(sizeof(xmlSchemaElement));
    if (ret == NULL) {
        xmlSchemaPErrMemory(ctxt, "allocating element", NULL);
        return (NULL);
    }
    memset(ret, 0, sizeof(xmlSchemaElement));
    ret->type = XML_SCHEMA_TYPE_ELEMENT;
    ret->name = name;
    ret->targetNamespace = nsName;
    ret->node = node;

    if (topLevel)
        WXS_ADD_GLOBAL(ctxt, ret);
    else
        WXS_ADD_LOCAL(ctxt, ret);
    WXS_ADD_PENDING(ctxt, ret);
    return (ret);
}
