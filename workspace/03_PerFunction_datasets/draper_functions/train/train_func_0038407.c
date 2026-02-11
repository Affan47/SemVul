setName(const DOMString& name)
{
    if (m_name) m_name->deref();
    m_name = name.implementation();
    setAttribute( ATTR_NAME, name );
    if (m_name) m_name->ref();
}
