CorrectEditorWidgetSizeX()
{
    int secWid = 0;


    int newSplitterx = m_pState->DoGetSplitterPosition(0);
    int newWidth = newSplitterx + m_pState->m_colWidths[1];

    if ( m_wndEditor2 )
    {

        wxRect r = m_wndEditor2->GetRect();
        secWid = r.width;
        r.x = newWidth - secWid;

        m_wndEditor2->SetSize( r );


#ifdef __WXMAC__
        if ( m_wndEditor )
#else
        if ( m_wndEditor && m_wndEditor->IsKindOf(CLASSINFO(wxTextCtrl)) )
#endif
            secWid += wxPG_TEXTCTRL_AND_BUTTON_SPACING;
    }

    if ( m_wndEditor )
    {
        wxRect r = m_wndEditor->GetRect();

        r.x = newSplitterx+m_ctrlXAdjust;

        if ( !(m_iFlags & wxPG_FL_FIXED_WIDTH_EDITOR) )
            r.width = newWidth - r.x - secWid;

        m_wndEditor->SetSize(r);
    }

    if ( m_wndEditor2 )
        m_wndEditor2->Refresh();
}
