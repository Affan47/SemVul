OnCompilerStarted(CodeBlocksEvent& event)
{
    if (m_Project && IsAttached() && m_IsVersioned[event.GetProject()])
    {
        if (m_Modified)
        {
            const bool doAutoIncrement = GetConfig().Settings.DoAutoIncrement;
            const bool askToIncrement = GetConfig().Settings.AskToIncrement;
            if (doAutoIncrement && askToIncrement)
            {
                if (wxMessageBox(_("Do you want to increment the version?"),_T(""),wxYES_NO) == wxYES)
                {
                    CommitChanges();
                }
            }
            else if(doAutoIncrement)
            {
                CommitChanges();
            }
        }
    }
}
