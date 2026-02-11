setSelfContactId(const QContactLocalId& contactId, QContactManager::Error* error)
{
    if (contactId == QContactLocalId(0) || d->m_contactIds.contains(contactId)) {
        *error = QContactManager::NoError;
        QContactLocalId oldId = d->m_selfContactId;
        d->m_selfContactId = contactId;

        QContactChangeSet changeSet;
        changeSet.setOldAndNewSelfContactId(QPair<QContactLocalId, QContactLocalId>(oldId, contactId));
        d->emitSharedSignals(&changeSet);
        return true;
    }

    *error = QContactManager::DoesNotExistError;
    return false;
}
