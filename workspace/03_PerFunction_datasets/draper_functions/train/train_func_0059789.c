TokenExists(const wxString& name, const wxString& baseArgs, const TokenIdxSet& parents, TokenKind kind)
{
    int idx = m_Tree.GetItemNo(name);
    if (!idx)
        return -1;

    TokenIdxSet::const_iterator it;
    TokenIdxSet& curList = m_Tree.GetItemAtPos(idx);
    int result = -1;
    for (it = curList.begin(); it != curList.end(); ++it)
    {
        result = *it;
        if (result < 0 || (size_t)result >= m_Tokens.size())
            continue;

        const Token* curToken = m_Tokens[result];
        if (!curToken)
            continue;

        if (curToken->m_TokenKind == kind && curToken->m_BaseArgs == baseArgs)
        {
            for ( TokenIdxSet::const_iterator pIt = parents.begin();
                  pIt != parents.end(); ++pIt )
            {
                if (curToken->m_ParentIndex == *pIt)
                    return result;
            }
        }
    }

    return -1;
}
