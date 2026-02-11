setChallenge(const QByteArray &c, const KUrl &resource,
                                           const QByteArray &httpMethod)
{
    QString oldUsername, oldPassword;
    if (!m_finalAuthStage && !m_username.isEmpty() && !m_password.isEmpty()) {
        oldUsername = m_username;
        oldPassword = m_password;
    }
    KAbstractHttpAuthentication::setChallenge(c, resource, httpMethod);
    if (!oldUsername.isEmpty() && !oldPassword.isEmpty()) {
        m_username = oldUsername;
        m_password = oldPassword;
    }


    m_needCredentials = m_challenge.isEmpty();
}
