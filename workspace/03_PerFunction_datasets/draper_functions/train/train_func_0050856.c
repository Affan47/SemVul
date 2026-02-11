start()
{
    if (!m_gameMachine.isRunning()) {
        buildMachine();
        kDebug() << "Starting machine";
        m_gameMachine.start();
        qApp->processEvents();
        kDebug() << "Machine state" << m_gameMachine.isRunning();
    }
}
