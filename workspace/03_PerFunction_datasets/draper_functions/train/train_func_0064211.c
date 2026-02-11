start(const QString &command)
{
    stop();
    m_process.start(command.toLatin1());
    if (!m_process.waitForStarted()) {
        m_response = "Unable to execute command: " + command;
        kDebug() << m_response;
        return false;
    }
    m_engineCommand = command;


    m_process.write("name\n");
    m_process.waitForReadyRead();
    QString response = m_process.readAllStandardOutput();
    if (response.isEmpty() || !response.startsWith(QLatin1String("="))) {
        m_response = "Game did not respond to GTP command \"name\"";
        kDebug() << m_response;
        stop();
        return false;
    } else {
        m_engineName = m_response;
    }


    m_process.write("version\n");
    if (waitResponse()) {
        m_engineVersion = m_response;
    }
    return true;
}
