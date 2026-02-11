OnHover( wxHtmlCellEvent& event )
{
    long i = 0;
    wxHtmlCell* pCell = event.GetCell();
    wxHtmlCell* pRootCell = pCell->GetRootCell();
    wxString strNvidiaIcon = wxT("nvidiaicon");
    wxString strATIIcon = wxT("atiicon");
    wxString strWebsiteIcon = wxT("website");
    wxString strTooltip = wxEmptyString;

    wxHtmlCell* pAnchor = pCell->GetParent()->GetFirstChild();

    if (pAnchor->Find(wxHTML_COND_ISANCHOR, &strNvidiaIcon)) {
        strTooltip = _("Nvidia GPU Supported");
    } else if (pAnchor->Find(wxHTML_COND_ISANCHOR, &strATIIcon)) {
        strTooltip = _("ATI GPU Supported");
    } else if (pAnchor->Find(wxHTML_COND_ISANCHOR, &strWebsiteIcon)) {
        strTooltip = _("Project Website");
    } else {

        pRootCell->GetId().ToLong(&i);

        strTooltip = m_Items[i]->GetDescription();
    }


    SetToolTip(strTooltip);
}
