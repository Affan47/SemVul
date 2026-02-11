ajDomImplementationCreateDocument(const AjPStr uri,
                                                 const AjPStr qualname,
                                                 AjPDomDocumentType doctype)
{
    const char *p = NULL;

    (void) uri;

    if(qualname)
        p = MAJSTRGETPTR(qualname);

    return ajDomImplementationCreateDocumentC(NULL, p, doctype);
}
