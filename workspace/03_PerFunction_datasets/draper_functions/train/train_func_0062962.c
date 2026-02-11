xmlSchemaGetNodeContent(xmlSchemaParserCtxtPtr ctxt, xmlNodePtr node)
{
    xmlChar *val;
    const xmlChar *ret;

    val = xmlNodeGetContent(node);
    if (val == NULL)
        val = xmlStrdup((xmlChar *)"");
    ret = xmlDictLookup(ctxt->dict, val, -1);
    xmlFree(val);
    return(ret);
}
