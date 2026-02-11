setPopupFiles(const KUrl::List& files)
{
    d->m_popupFiles = files;
    if (files.isEmpty()) {
        d->m_newMenuGroup->setEnabled(false);
    } else {
        KUrl firstUrl = files.first();
        if (KProtocolManager::supportsWriting(firstUrl)) {
            d->m_newMenuGroup->setEnabled(true);
            if (d->m_newDirAction) {
                d->m_newDirAction->setEnabled(KProtocolManager::supportsMakeDir(firstUrl));
            }
        } else {
            d->m_newMenuGroup->setEnabled(true);
        }
    }
}
