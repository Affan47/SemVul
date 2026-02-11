tags()
{
    QStringList result;
    m_process.start(QLatin1String("git tag"));
    while (m_process.waitForReadyRead()) {
        char buffer[BUFFER_SIZE];
        while (m_process.readLine(buffer, sizeof(buffer)) > 0){
            const QString tagName = m_localCodec->toUnicode(buffer).trimmed();
            result.append(tagName);
        }
    }
    return result;
}
