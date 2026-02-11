getRDF()
{
    FV_View* view = getView();
    PD_Document* doc = view->getDocument();
    PD_DocumentRDFHandle rdf = doc->getDocumentRDF();
    return rdf;
}
