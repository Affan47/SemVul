xmlSchemaAddIDC(xmlSchemaParserCtxtPtr ctxt, xmlSchemaPtr schema,
                  const xmlChar *name, const xmlChar *nsName,
                  int category, xmlNodePtr node)
{
    xmlSchemaIDCPtr ret = NULL;

    if ((ctxt == NULL) || (schema == NULL) || (name == NULL))
        return (NULL);

    ret = (xmlSchemaIDCPtr) xmlMalloc(sizeof(xmlSchemaIDC));
    if (ret == NULL) {
        xmlSchemaPErrMemory(ctxt,
            "allocating an identity-constraint definition", NULL);
        return (NULL);
    }
    memset(ret, 0, sizeof(xmlSchemaIDC));

    ret->targetNamespace = nsName;
    ret->name = name;
    ret->type = category;
    ret->node = node;

    WXS_ADD_GLOBAL(ctxt, ret);


    if (category == XML_SCHEMA_TYPE_IDC_KEYREF)
        WXS_ADD_PENDING(ctxt, ret);
    return (ret);
}
