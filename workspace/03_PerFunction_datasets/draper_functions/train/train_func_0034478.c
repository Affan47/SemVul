onLogout(bool clean)
{
    getConnection()->unregisterRouterForTo(m_router, m_account->getId());
}
