setQuitOnLastInstanceClosed(bool quit)
{
    m_quit = quit;
    if(m_quit){
        connect(InstanceManager::instance(), SIGNAL(allInstancesClosed()), QCoreApplication::instance(), SLOT(quit()));
    }
    else {
        disconnect(InstanceManager::instance(), SIGNAL(allInstancesClosed()), QCoreApplication::instance(), SLOT(quit()));
    }
}
