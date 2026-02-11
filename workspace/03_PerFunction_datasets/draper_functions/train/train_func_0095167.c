UpdateListbookImages()
{
    wxListbook* lb = XRCCTRL(*this, "nbMain", wxListbook);
    int sel = lb->GetSelection();

    if (SettingsIconsStyle(XRCCTRL(*this, "rbSettingsIconsSize", wxRadioBox)->GetSelection()) == sisNoIcons)
    {
        SetSettingsIconsStyle(lb->GetListView(), sisNoIcons);
        lb->SetImageList(nullptr);
    }
    else
    {
        lb->SetImageList(m_pImageList);

        for (size_t i = 0; i < IMAGES_COUNT + m_PluginPanels.GetCount(); ++i)
            lb->SetPageImage(i, (i * 2) + (sel == (int)i ? 0 : 1));
        SetSettingsIconsStyle(lb->GetListView(), sisLargeIcons);
    }


    wxString label = lb->GetPageText(sel);

    while (label.Replace(_T(" & "), _T(" && ")))
        ;
    XRCCTRL(*this, "lblBigTitle", wxStaticText)->SetLabel(label);
    XRCCTRL(*this, "pnlTitleInfo", wxPanel)->Layout();
}
