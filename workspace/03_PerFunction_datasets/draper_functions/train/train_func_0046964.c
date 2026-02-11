xmlSchemaCheckCSelectorXPath(xmlSchemaParserCtxtPtr ctxt,
                             xmlSchemaIDCPtr idc,
                             xmlSchemaIDCSelectPtr selector,
                             xmlAttrPtr attr,
                             int isField)
{
    xmlNodePtr node;


    if (selector == NULL) {
        xmlSchemaPErr(ctxt, idc->node,
            XML_SCHEMAP_INTERNAL,
            "Internal error: xmlSchemaCheckCSelectorXPath, "
            "the selector is not specified.\n", NULL, NULL);
        return (-1);
    }
    if (attr == NULL)
        node = idc->node;
    else
        node = (xmlNodePtr) attr;
    if (selector->xpath == NULL) {
        xmlSchemaPCustomErr(ctxt,

            XML_SCHEMAP_S4S_ATTR_INVALID_VALUE,
            NULL, node,
            "The XPath expression of the selector is not valid", NULL);
        return (XML_SCHEMAP_S4S_ATTR_INVALID_VALUE);
    } else {
        const xmlChar **nsArray = NULL;
        xmlNsPtr *nsList = NULL;


        if (attr == NULL)
            nsList = NULL;
        else
            nsList = xmlGetNsList(attr->doc, attr->parent);


        if (nsList != NULL) {
            int i, count = 0;

            for (i = 0; nsList[i] != NULL; i++)
                count++;

            nsArray = (const xmlChar **) xmlMalloc(
                (count * 2 + 1) * sizeof(const xmlChar *));
            if (nsArray == NULL) {
                xmlSchemaPErrMemory(ctxt, "allocating a namespace array",
                    NULL);
                xmlFree(nsList);
                return (-1);
            }
            for (i = 0; i < count; i++) {
                nsArray[2 * i] = nsList[i]->href;
                nsArray[2 * i + 1] = nsList[i]->prefix;
            }
            nsArray[count * 2] = NULL;
            xmlFree(nsList);
        }


        if (isField)
            selector->xpathComp = (void *) xmlPatterncompile(selector->xpath,
                NULL, XML_PATTERN_XSFIELD, nsArray);
        else
            selector->xpathComp = (void *) xmlPatterncompile(selector->xpath,
                NULL, XML_PATTERN_XSSEL, nsArray);
        if (nsArray != NULL)
            xmlFree((xmlChar **) nsArray);

        if (selector->xpathComp == NULL) {
            xmlSchemaPCustomErr(ctxt,

                XML_SCHEMAP_S4S_ATTR_INVALID_VALUE,
                NULL, node,
                "The XPath expression '%s' could not be "
                "compiled", selector->xpath);
            return (XML_SCHEMAP_S4S_ATTR_INVALID_VALUE);
        }
    }
    return (0);
}
