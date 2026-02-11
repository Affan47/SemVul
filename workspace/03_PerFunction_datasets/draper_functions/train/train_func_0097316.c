getAttribute( const DOMString &name )
{
    LocalName localname;
    PrefixName prefixname;
    splitPrefixLocalName(name, prefixname, localname, m_htmlCompat);
    if (!localname.id()) return DOMString();
    return getAttribute(makeId(emptyNamespace, localname.id()), prefixname, false );
}
