closeScannerProcess()
{
    if( !m_scanner )
        return;

    m_scanner->close();
    m_scanner->waitForFinished();
    delete m_scanner;
    m_scanner = 0;
}
