create(const char* ,
                                         QWidget* wparent,
                                         QObject *parent,
                                         const QVariantList &,
                                         const QString& )
{
    return new AdaptorView(wparent, parent, QStringList());
}
