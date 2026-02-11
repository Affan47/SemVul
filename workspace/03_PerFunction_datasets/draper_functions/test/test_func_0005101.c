InternalGetEditorBase(int page)
{
    if (page >= 0 && page < (int)m_pNotebook->GetPageCount())
    {
        return static_cast<EditorBase*>(m_pNotebook->GetPage(page));
    }
    return nullptr;
}
