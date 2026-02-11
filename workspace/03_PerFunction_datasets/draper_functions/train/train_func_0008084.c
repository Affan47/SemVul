ajDomImplementationCreateDocumentC(const char *uri,
                                                  const char *qualname,
                                                  AjPDomDocumentType doctype)
{
    AjPDomDocument doc     = NULL;
    AjPDomElement  element = NULL;

    (void) uri;

    if(!(doc = ajDomDocumentCreateNode(NULL, ajEDomNodeTypeDocumentNode)))
    {
        ajDebug("ajDomImplementationCreateDocumentC: document memory\n");
        return NULL;
    }

    doc->name = ajStrNew();
    ajStrAssignC(&doc->name, "#document");

    if(doctype)
        ajDomNodeAppendChild(doc, doctype);

    if(qualname)
        if(strlen(qualname))
        {
            element = ajDomDocumentCreateElementC(doc, qualname);
            if(!element)
            {
                ajDebug("ajDomImplementationCreateDocumentC: element memory\n");
                ajDomDocumentDestroyNode(doc, &doc);

                return NULL;
            }

            ajDomNodeAppendChild(doc, element);
        }

    return doc;
}
