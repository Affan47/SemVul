findServiceTypeByName(const QString &_name)
{
    assert (KSycoca::self()->isBuilding());

    KSycocaEntry::Ptr servType = m_entryDict->value( _name );
    return KServiceType::Ptr::staticCast( servType );
}
