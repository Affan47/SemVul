ajDomDocumentCreateEntityReferenceC(AjPDomDocument doc,
                                                          const char *name)
{
    AjPDomEntityReference eref = NULL;

    eref = ajDomDocumentCreateNode(doc, ajEDomNodeTypeEntityReference);

    if(!eref)
        return NULL;

    eref->name = ajStrNewC(name);

    return eref;
}
