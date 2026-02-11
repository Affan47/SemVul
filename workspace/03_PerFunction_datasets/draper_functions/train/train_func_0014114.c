xmlSchemaAddRedef(xmlSchemaParserCtxtPtr pctxt,
                  xmlSchemaBucketPtr targetBucket,
                  void *item,
                  const xmlChar *refName,
                  const xmlChar *refTargetNs)
{
    xmlSchemaRedefPtr ret;

    ret = (xmlSchemaRedefPtr)
        xmlMalloc(sizeof(xmlSchemaRedef));
    if (ret == NULL) {
        xmlSchemaPErrMemory(pctxt,
            "allocating redefinition info", NULL);
        return (NULL);
    }
    memset(ret, 0, sizeof(xmlSchemaRedef));
    ret->item = item;
    ret->targetBucket = targetBucket;
    ret->refName = refName;
    ret->refTargetNs = refTargetNs;
    if (WXS_CONSTRUCTOR(pctxt)->redefs == NULL)
        WXS_CONSTRUCTOR(pctxt)->redefs = ret;
    else
        WXS_CONSTRUCTOR(pctxt)->lastRedef->next = ret;
    WXS_CONSTRUCTOR(pctxt)->lastRedef = ret;

    return (ret);
}
