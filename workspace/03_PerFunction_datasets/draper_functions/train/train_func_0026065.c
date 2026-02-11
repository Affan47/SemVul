CollapseItem(wxTreeItemId item)
{
    TRACE(_T("ClassBrowserBuilderThread::CollapseItem"));

    if (CBBT_SANITY_CHECK || !item.IsOk())
        return;

    bool locked = false;
    if (m_InitDone)
    {
        CC_LOCKER_TRACK_CBBT_MTX_LOCK(m_ClassBrowserBuilderThreadMutex)
        locked = true;
    }

#if !defined(__WXGTK__) && !defined(__WXMAC__)
    m_CCTreeCtrlTop->CollapseAndReset(item);
#else
    m_CCTreeCtrlTop->DeleteChildren(item);
#endif
    m_CCTreeCtrlTop->SetItemHasChildren(item);

    if (locked)
        CC_LOCKER_TRACK_CBBT_MTX_UNLOCK(m_ClassBrowserBuilderThreadMutex)
}
