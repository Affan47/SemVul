updateAppearance()
{
    Q_DEBUG_BLOCK;

    if ( !The::settings().showTrayIcon() )
        m_trayIcon->hide();
    else
        m_trayIcon->show();
}
