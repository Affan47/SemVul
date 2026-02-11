CreateColoursSample()
{
    if (!m_TextColourControl)
    {
        m_TextColourControl = new cbStyledTextCtrl(this, wxID_ANY);

        m_TextColourControl->SetTabWidth(4);
        m_TextColourControl->SetCaretWidth(0);
        m_TextColourControl->SetMarginType(0, wxSCI_MARGIN_NUMBER);
        m_TextColourControl->SetMarginWidth(0, 32);
        m_TextColourControl->SetMinSize(wxSize(50,50));
        m_TextColourControl->SetMarginWidth(1, 0);

        wxXmlResource::Get()->AttachUnknownControl(_T("txtColoursSample"), m_TextColourControl);
    }

    int breakLine = -1;
    int debugLine = -1;
    int errorLine = -1;
    wxString code = m_Theme->GetSampleCode(m_Lang, &breakLine, &debugLine, &errorLine);
    if (!code.IsEmpty())
    {
        m_TextColourControl->SetReadOnly(false);
        m_TextColourControl->LoadFile(code);
        m_TextColourControl->SetReadOnly(true);
    }

    m_TextColourControl->MarkerDeleteAll(2);
    m_TextColourControl->MarkerDeleteAll(3);
    m_TextColourControl->MarkerDeleteAll(4);
    if (breakLine != -1) m_TextColourControl->MarkerAdd(breakLine, 2);
    if (debugLine != -1) m_TextColourControl->MarkerAdd(debugLine, 3);
    if (errorLine != -1) m_TextColourControl->MarkerAdd(errorLine, 4);

    ApplyColours();
    FillColourComponents();
}
