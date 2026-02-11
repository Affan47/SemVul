GetAccountsNumber()
{

    if (m_accountsNumber)
        return m_accountsNumber;


    std::set<uint32> accountsIdSet;
    for (MemberList::const_iterator itr = members.begin(); itr != members.end(); ++itr)
        accountsIdSet.insert(itr->second.accountId);

    m_accountsNumber = accountsIdSet.size();

    return m_accountsNumber;
}
