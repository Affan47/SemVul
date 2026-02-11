postProcessServices()
{


    KSycocaEntryDict::Iterator itserv = m_entryDict->begin();
    const KSycocaEntryDict::Iterator endserv = m_entryDict->end();
    for( ; itserv != endserv ; ++itserv ) {

        KSycocaEntry::Ptr entry = *itserv;
        KService::Ptr service = KService::Ptr::staticCast(entry);

        if (!service->isDeleted()) {
            const QString parent = service->parentApp();
            if (!parent.isEmpty())
                m_serviceGroupFactory->addNewChild(parent, KSycocaEntry::Ptr::staticCast(service));
        }

        const QString name = service->desktopEntryName();
        m_nameDict->add(name, entry);
        m_nameMemoryHash.insert(name, service);

        const QString relName = service->entryPath();

        m_relNameDict->add(relName, entry);
        m_relNameMemoryHash.insert(relName, service);

        const QString menuId = service->menuId();
        if (!menuId.isEmpty()) {
            m_menuIdDict->add(menuId, entry);
            m_menuIdMemoryHash.insert(menuId, service);
        }
    }
    populateServiceTypes();
}
