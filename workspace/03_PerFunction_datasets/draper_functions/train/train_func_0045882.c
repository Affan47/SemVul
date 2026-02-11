setFaceType(const QString& facetype)
{
    int i = KPageView::staticMetaObject.indexOfEnumerator("FaceType");
    Q_ASSERT( i >= 0 );
    QMetaEnum e = KPageView::staticMetaObject.enumerator(i);
    int v = e.keysToValue( facetype.toUtf8() );
    if( v < 0 )
        return false;
    KPageDialog::setFaceType( (KPageDialog::FaceType) v );
    return true;
}
