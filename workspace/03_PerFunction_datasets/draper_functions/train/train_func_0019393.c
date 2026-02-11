scheduleCommand(const Command &command)
{
    if (!m_commandTimer) {
        m_commandTimer = new QTimer(this);
        m_commandTimer->setSingleShot(true);
        connect(m_commandTimer, SIGNAL(timeout()), this, SLOT(slotProcessQueue()));
    }
    m_commands.append(command);
    m_commandTimer->start(0);
}
