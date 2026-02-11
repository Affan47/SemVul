xmlSchemaCheckFacetValues(xmlSchemaTypePtr typeDecl,
                          xmlSchemaParserCtxtPtr pctxt)
{
    int res, olderrs = pctxt->nberrors;
    const xmlChar *name = typeDecl->name;


    if (typeDecl->facets != NULL) {
        xmlSchemaFacetPtr facet = typeDecl->facets;


        if (pctxt->vctxt == NULL) {
            if (xmlSchemaCreateVCtxtOnPCtxt(pctxt) == -1)
                return(-1);
        }
        pctxt->vctxt->schema = pctxt->schema;
        while (facet != NULL) {
            res = xmlSchemaCheckFacet(facet, typeDecl, pctxt, name);
            HFAILURE
            facet = facet->next;
        }
        pctxt->vctxt->schema = NULL;
    }
    if (olderrs != pctxt->nberrors)
        return(pctxt->err);
    return(0);
exit_failure:
    return(-1);
}
