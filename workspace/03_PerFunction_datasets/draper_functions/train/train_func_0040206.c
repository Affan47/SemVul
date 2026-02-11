findGroupRight(WinClient &winclient) {
    Groupables::iterator it = m_expecting_groups.find(winclient.window());
    if (it == m_expecting_groups.end())
        return 0;


    WinClient *other = it->second;
    m_expecting_groups.erase(it);


    Window leftwin = other->getGroupLeftWindow();
    if (leftwin != None && leftwin != winclient.window())
        return 0;

    return other;
}
