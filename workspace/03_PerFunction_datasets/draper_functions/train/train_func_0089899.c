settingsQuery(const QString& provider, const QString& id)
{
    if (!provider.isEmpty()) {
        return QString("Settings\\provider:%1\\id:%2").arg(escape(provider)).arg(escape(id));
    } else {
        return QString();
    }
}
