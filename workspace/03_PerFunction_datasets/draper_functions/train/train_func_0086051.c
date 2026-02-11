OnEditFilemasks(cb_unused wxCommandEvent& event)
{
    if (m_Theme && m_Lang != HL_NONE)
    {
        wxString masks = wxGetTextFromUser(_("Edit filemasks (use commas to separate them - case insensitive):"),
                                        m_Theme->GetLanguageName(m_Lang),
                                        GetStringFromArray(m_Theme->GetFileMasks(m_Lang), _T(",")));
        if (!masks.IsEmpty())
            m_Theme->SetFileMasks(m_Lang, masks);
    }
}
