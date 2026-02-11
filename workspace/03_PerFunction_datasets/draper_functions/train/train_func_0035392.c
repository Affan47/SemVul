error(int , const QString &)
{
    if ( m_styleSheet ) {
        m_styleSheet->setParent(0);
        m_styleSheet->deref();
    }
    m_styleSheet = 0;

    m_loading = false;
    m_done = true;

    checkLoaded();
}
