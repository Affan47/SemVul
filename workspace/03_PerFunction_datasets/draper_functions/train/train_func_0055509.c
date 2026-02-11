xmlSchemaIDCAcquireBinding(xmlSchemaValidCtxtPtr vctxt,
                          xmlSchemaIDCMatcherPtr matcher)
{
    xmlSchemaNodeInfoPtr ielem;

    ielem = vctxt->elemInfos[matcher->depth];

    if (ielem->idcTable == NULL) {
        ielem->idcTable = xmlSchemaIDCNewBinding(matcher->aidc->def);
        if (ielem->idcTable == NULL)
            return (NULL);
        return(ielem->idcTable);
    } else {
        xmlSchemaPSVIIDCBindingPtr bind = NULL;

        bind = ielem->idcTable;
        do {
            if (bind->definition == matcher->aidc->def)
                return(bind);
            if (bind->next == NULL) {
                bind->next = xmlSchemaIDCNewBinding(matcher->aidc->def);
                if (bind->next == NULL)
                    return (NULL);
                return(bind->next);
            }
            bind = bind->next;
        } while (bind != NULL);
    }
    return (NULL);
}
