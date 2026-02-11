OnResetDefaultColours(cb_unused wxCommandEvent& event)
{
    wxAuiDockArt* art = new wxAuiDefaultDockArt;

    XRCCTRL(*this, "spnAuiBorder", wxSpinCtrl)->SetValue(art->GetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE));
    XRCCTRL(*this, "spnAuiSash", wxSpinCtrl)->SetValue(art->GetMetric(wxAUI_DOCKART_SASH_SIZE));
    XRCCTRL(*this, "spnAuiCaption", wxSpinCtrl)->SetValue(art->GetMetric(wxAUI_DOCKART_CAPTION_SIZE));
    XRCCTRL(*this, "btnAuiActiveCaptionColour", wxButton)->SetBackgroundColour(art->GetColour(wxAUI_DOCKART_ACTIVE_CAPTION_COLOUR));
    XRCCTRL(*this, "btnAuiActiveCaptionGradientColour", wxButton)->SetBackgroundColour(art->GetColour(wxAUI_DOCKART_ACTIVE_CAPTION_GRADIENT_COLOUR));
    XRCCTRL(*this, "btnAuiActiveCaptionTextColour", wxButton)->SetBackgroundColour(art->GetColour(wxAUI_DOCKART_ACTIVE_CAPTION_TEXT_COLOUR));
    XRCCTRL(*this, "btnAuiInactiveCaptionColour", wxButton)->SetBackgroundColour(art->GetColour(wxAUI_DOCKART_INACTIVE_CAPTION_COLOUR));
    XRCCTRL(*this, "btnAuiInactiveCaptionGradientColour", wxButton)->SetBackgroundColour(art->GetColour(wxAUI_DOCKART_INACTIVE_CAPTION_GRADIENT_COLOUR));
    XRCCTRL(*this, "btnAuiInactiveCaptionTextColour", wxButton)->SetBackgroundColour(art->GetColour(wxAUI_DOCKART_INACTIVE_CAPTION_TEXT_COLOUR));

    delete art;
}
