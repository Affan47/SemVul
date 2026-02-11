addMessage(const QString &object, const QString &msg, bool forceWarning)
{
    if (!m_MuteConsole || forceWarning) {
        QString m = lineWrapString(msg, 90-26);
        m = indentString(m, 26).mid(26);
        qWarning() << QString("%1 %2")
                      .arg(object.leftJustified(25, QChar(' ')))
                      .arg(m);
    }
    addData(object, msg, QDateTime::currentDateTime(), LogData::Message);
}
