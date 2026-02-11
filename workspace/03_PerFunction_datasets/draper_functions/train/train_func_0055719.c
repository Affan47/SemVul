EnableToolbarTools(bool enable)
{
    if (m_Scope)
        m_Scope->Enable(enable);
    if (m_Function)
        m_Function->Enable(enable);
}
