NPClass_SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *result)
{
    NPClass_Prolog;
    const QByteArray qname = NPN_UTF8FromIdentifier(name);
    QVariant qvar = *result;
    return qobject->setProperty(qname, qvar);
}
