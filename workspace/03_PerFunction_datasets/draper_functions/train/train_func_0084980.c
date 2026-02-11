login(const std::string &uname, const std::string &password)
{
    if (!m_con->isConnected()) {
        error() << "called login on unconnected Connection";
        return NOT_CONNECTED;
    }

    if (m_status != DISCONNECTED) {
        error() << "called login, but state is not currently disconnected";
        return ALREADY_LOGGED_IN;
    }

    return internalLogin(uname, password);
}
