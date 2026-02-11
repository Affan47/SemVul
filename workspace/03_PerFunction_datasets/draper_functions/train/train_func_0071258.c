firstTimeRunning(const QString &subProcess) const
{
    if (subProcess.isEmpty())
        return m_NetworkSettings->value("FirstTimeRunning", true).toBool();
    return m_UserSettings->value("FirstTimeRunning/" + subProcess, true).toBool();
}
