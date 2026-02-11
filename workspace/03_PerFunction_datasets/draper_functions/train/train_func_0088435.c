NPClass_GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result)
{
    NPClass_Prolog;
    const QByteArray qname = NPN_UTF8FromIdentifier(name);
    QVariant qvar = qobject->property(qname);
    if (!qvar.isValid()) {
        NPN_SetException(npobj, QByteArray("Failed to get value for property " + qname).constData());
        return false;
    }
    *result = NPVariant::fromQVariant(This, qvar);
    return true;
}
