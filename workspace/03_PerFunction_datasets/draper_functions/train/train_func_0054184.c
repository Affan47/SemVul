setContact(const QContact& contact)
{
    Q_D(QContactSaveRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_contacts.clear();
    d->m_contacts.append(contact);
}
