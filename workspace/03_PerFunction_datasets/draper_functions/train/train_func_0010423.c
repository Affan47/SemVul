createNativeAnnot(::Page *destPage, DocumentData *doc)
{

    TextAnnotation *q = static_cast<TextAnnotation*>( makeAlias() );


    pdfPage = destPage;
    parentDoc = doc;


    PDFRectangle rect = boundaryToPdfRectangle(boundary, flags);
    if (textType == TextAnnotation::Linked)
    {
        pdfAnnot = new AnnotText(destPage->getDoc(), &rect);
    }
    else
    {
        GooString * da = toAppearanceString(textFont);
        pdfAnnot = new AnnotFreeText(destPage->getDoc(), &rect, da);
        delete da;
    }


    flushBaseAnnotationProperties();
    q->setTextIcon(textIcon);
    q->setInplaceAlign(inplaceAlign);
    q->setCalloutPoints(inplaceCallout);
    q->setInplaceIntent(inplaceIntent);

    delete q;

    inplaceCallout.clear();

    return pdfAnnot;
}
