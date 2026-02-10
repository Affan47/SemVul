setContents( const QString &contents )
{
    Q_D( Annotation );

    if (!d->pdfAnnot)
    {
        d->contents = contents;
        return;
    }

    GooString *s = QStringToUnicodeGooString(contents);
    d->pdfAnnot->setContents(s);
    delete s;
}
