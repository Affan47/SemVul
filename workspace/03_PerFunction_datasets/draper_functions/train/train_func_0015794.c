handleLogoutTimeout()
{
    error() << "LOGOUT timed out waiting for response";

    m_status = DISCONNECTED;
    deleteLater(m_timeout.release());

    LogoutComplete.emit(false);
}
