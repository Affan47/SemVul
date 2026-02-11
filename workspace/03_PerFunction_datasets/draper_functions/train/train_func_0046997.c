xmlSchemaFreeAttributeUse(xmlSchemaAttributeUsePtr use)
{
    if (use == NULL)
        return;
    if (use->annot != NULL)
        xmlSchemaFreeAnnot(use->annot);
    if (use->defVal != NULL)
        xmlSchemaFreeValue(use->defVal);
    xmlFree(use);
}
