setStampIconName( const QString &name )
{
    Q_D( StampAnnotation );

    if (!d->pdfAnnot)
    {
        d->stampIconName = name;
        return;
    }

    AnnotStamp * stampann = static_cast<AnnotStamp*>(d->pdfAnnot);
    QByteArray encoded = name.toLatin1();
    GooString s(encoded.constData());
    stampann->setIcon(&s);
}
