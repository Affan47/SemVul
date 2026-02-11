ShowModal (long style) {
    UpdateDirHistory ();
    UpdateFindHistory ();
    UpdateReplaceHistory ();
    m_style = style;
    if (m_style & myFR_REPLACEDIALOG) {
        SetTitle(_("Find and Replace"));
        m_findpane->Show (m_fdirsizer, false);
        m_findpane->Show (m_specsizer, false);
        m_findpane->Show (m_replsizer, true);
        m_optionsizer->Show (m_wholeword, true);
        m_optionsizer->Show (m_subfolder, false);
        m_dirssizer->Show (m_direction, true);
        m_buttonpane->Show (m_replaceButton, true);
        m_buttonpane->Show (m_replaceAllButton, true);
    }else if (m_style & myFR_FINDINFILES) {
        SetTitle(_("Find in Files"));
        m_findpane->Show (m_fdirsizer, true);
        m_findpane->Show (m_specsizer, true);
        m_findpane->Show (m_replsizer, false);
        m_optionsizer->Show (m_wholeword, false);
        m_optionsizer->Show (m_subfolder, true);
        m_dirssizer->Show (m_direction, false);
        m_buttonpane->Show (m_replaceButton, false);
        m_buttonpane->Show (m_replaceAllButton, false);
        m_wholeword->Enable (false);
    }else{
        SetTitle(_("Find"));
        m_findpane->Show (m_fdirsizer, false);
        m_findpane->Show (m_specsizer, false);
        m_findpane->Show (m_replsizer, false);
        m_optionsizer->Show (m_wholeword, true);
        m_optionsizer->Show (m_subfolder, false);
        m_dirssizer->Show (m_direction, true);
        m_buttonpane->Show (m_replaceButton, false);
        m_buttonpane->Show (m_replaceAllButton, false);
        m_wholeword->Enable (true);
    }
    m_direction->Enable (true);
    m_matchcase->Enable (!(style & myFR_NOMATCHCASE));
    m_wholeword->Enable (!(style & myFR_NOWHOLEWORD));
    m_findregex->Enable (!(style & myFR_NOFINDREGEX));
    m_findstr->SetFocus();
    m_findstr->SetSelection (-1, -1);
    Fit ();
    return wxScrollingDialog::ShowModal ();
}
