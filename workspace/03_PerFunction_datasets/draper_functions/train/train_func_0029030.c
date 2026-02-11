xmlSchemaGetType(xmlSchemaPtr schema, const xmlChar * name,
                 const xmlChar * nsName)
{
    xmlSchemaTypePtr ret = NULL;

    if (name == NULL)
        return (NULL);

    if ((nsName != NULL) && xmlStrEqual(nsName, xmlSchemaNs)) {
        ret = xmlSchemaGetPredefinedType(name, nsName);
        if (ret != NULL)
            goto exit;


    }
    if (schema != NULL) {
        WXS_FIND_GLOBAL_ITEM(typeDecl)
    }
exit:

#ifdef DEBUG
    if (ret == NULL) {
        if (nsName == NULL)
            fprintf(stderr, "Unable to lookup type %s", name);
        else
            fprintf(stderr, "Unable to lookup type %s:%s", name,
                    nsName);
    }
#endif
    return (ret);
}
