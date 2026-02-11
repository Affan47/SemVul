create(const QString &mimeType, const QUrl &url,
                                    const QStringList &argumentNames, const QStringList &argumentValues)
{
    load();
    if (!m_enabled)
        return 0;
    Q_UNUSED(mimeType);
    if (m_whitelist.contains(url.host()))
        return 0;

    ClickToFlash *ctf = new ClickToFlash(this);
    ctf->url = url;
    ctf->argumentNames = argumentNames;
    ctf->argumentValues = argumentValues;
    return ctf;
}
