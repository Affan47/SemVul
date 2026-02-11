OnMnuEditCopy(wxCommandEvent& event)
{
       if ( !IsAttached() )
    {
        event.Skip();
        return;
    }

    wxWindow* pFocused = wxWindow::FindFocus();


    if ( pFocused == m_pCboSearchExpr )
    {
        if ( m_pCboSearchExpr->CanCopy() )
            m_pCboSearchExpr->Copy();
        LOGIT( _T("OnMnuEditcopy for m_pCboSearchExpr") );
    }
    else if ( pFocused == m_pThreadSearchView->m_pCboSearchExpr )
    {
        if ( m_pThreadSearchView->m_pCboSearchExpr->CanCopy() )
            m_pThreadSearchView->m_pCboSearchExpr->Copy();
        LOGIT( _T("OnMnuEditcopy for m_pThreadSearchView->m_pCboSearchExpr") );
    }
    else if ( pFocused == static_cast<wxWindow*>(m_pThreadSearchView->m_pSearchPreview) )
    {
        bool hasSel = m_pThreadSearchView->m_pSearchPreview->GetSelectionStart() != m_pThreadSearchView->m_pSearchPreview->GetSelectionEnd();
        if (hasSel)
            m_pThreadSearchView->m_pSearchPreview->Copy();
        LOGIT( _T("OnMnuEditcopy for m_pSearchPreview") );
    }
    else
    {
        event.Skip();
    }


    return;
}
