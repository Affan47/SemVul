xmlSchemaEvalErrorNodeType(xmlSchemaAbstractCtxtPtr actxt,
                           xmlNodePtr node)
{
    if (node != NULL)
        return (node->type);
    if ((actxt->type == XML_SCHEMA_CTXT_VALIDATOR) &&
        (((xmlSchemaValidCtxtPtr) actxt)->inode != NULL))
        return ( ((xmlSchemaValidCtxtPtr) actxt)->inode->nodeType);
    return (-1);
}
