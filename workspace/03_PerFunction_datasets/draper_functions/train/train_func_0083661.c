UpdateFunctions(unsigned int scopeItem)
{
    m_Function->Freeze();
    m_Function->Clear();

    unsigned int idxEnd = (scopeItem + 1 < m_ScopeMarks.size()) ? m_ScopeMarks[scopeItem + 1] : m_FunctionsScope.size();
    for (unsigned int idxFn = m_ScopeMarks[scopeItem]; idxFn < idxEnd; ++idxFn)
    {
        const wxString &name = m_FunctionsScope[idxFn].Name;
        m_Function->Append(name);
    }

    m_Function->Thaw();
}
