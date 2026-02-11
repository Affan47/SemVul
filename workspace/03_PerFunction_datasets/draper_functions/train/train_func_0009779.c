operator<<(QDataStream& out, const QContact& contact)
{
    quint8 formatVersion = 1;
    return out << formatVersion << contact.id() << contact.details() << contact.d->m_preferences;
}
