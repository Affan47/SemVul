AddTokenToList(Token* newToken, int forceidx)
{
    if (!newToken)
        return -1;

    int result = -1;


    if (forceidx >= 0)
    {
        if ((size_t)forceidx >= m_Tokens.size())
        {
            int max = 250*((forceidx + 250) / 250);
            m_Tokens.resize((max),0);
        }
        m_Tokens[forceidx] = newToken;
        result = forceidx;
    }
    else
    {
        if (m_FreeTokens.size())
        {
            result = m_FreeTokens.back();
            m_FreeTokens.pop_back();
            m_Tokens[result] = newToken;
        }
        else
        {
            result = m_Tokens.size();
            m_Tokens.push_back(newToken);
        }
    }

    newToken->m_TokenTree = this;
    newToken->m_Index = result;


    newToken->m_FullType.Shrink();
    newToken->m_BaseType.Shrink();
    newToken->m_Name.Shrink();
    newToken->m_Args.Shrink();
    newToken->m_BaseArgs.Shrink();
    newToken->m_AncestorsString.Shrink();
    newToken->m_TemplateArgument.Shrink();

    return result;
}
