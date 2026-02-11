OnColourTheme(cb_unused wxCommandEvent& event)
{

    wxChoice* cmbThemes = XRCCTRL(*this, "cmbThemes", wxChoice);
    if (m_Theme && m_Theme->GetName() != cmbThemes->GetStringSelection())
    {
        if (AskToSaveTheme())
            ChangeTheme();
    }
}
