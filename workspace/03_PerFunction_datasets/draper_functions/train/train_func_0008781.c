handleLoginTimeout()
{
    m_status = DISCONNECTED;
    deleteLater(m_timeout.release());

    LoginFailure.emit("timed out waiting for server response");
}
