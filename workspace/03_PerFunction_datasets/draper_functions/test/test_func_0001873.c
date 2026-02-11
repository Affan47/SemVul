setInplaceAlign( int align )
{
    Q_D( TextAnnotation );

    if (!d->pdfAnnot)
    {
        d->inplaceAlign = align;
        return;
    }

    if (d->pdfAnnot->getType() == Annot::typeFreeText)
    {
        AnnotFreeText * ftextann = static_cast<AnnotFreeText*>(d->pdfAnnot);
        ftextann->setQuadding((AnnotFreeText::AnnotFreeTextQuadding)align);
    }
}
