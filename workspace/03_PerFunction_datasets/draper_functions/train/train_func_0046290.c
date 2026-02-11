getUriFrom(QObject *o) const
{
    Uri uri;
    QVariant uriVar = o->property("uri");

    if (uriVar != QVariant()) {
        if (Uri::hasUriType(uriVar)) {
            uri = uriVar.value<Uri>();
        } else {
            uri = m_s->expand(uriVar.toString());
        }
    }

    return uri;
}
