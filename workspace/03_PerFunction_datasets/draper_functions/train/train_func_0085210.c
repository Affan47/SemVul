OnSaveState(wxConfigBase* pConfig) {
    wxString    strBaseConfigLocation = wxEmptyString;
    wxListItem  liColumnInfo;
    wxInt32     iIndex = 0;
    wxInt32     iColumnCount = 0;


    wxASSERT(pConfig);


    strBaseConfigLocation = pConfig->GetPath() + wxT("/");


    iColumnCount = GetColumnCount() - 1;


    liColumnInfo.SetMask(
        wxLIST_MASK_TEXT |
        wxLIST_MASK_WIDTH |
        wxLIST_MASK_FORMAT
    );


    for (iIndex = 0; iIndex <= iColumnCount; iIndex++) {
        GetColumn(iIndex, liColumnInfo);

        pConfig->SetPath(strBaseConfigLocation + liColumnInfo.GetText());

        pConfig->Write(wxT("Width"), liColumnInfo.GetWidth());

#if (defined(__WXMAC__) &&  wxCHECK_VERSION(2,8,0))
        pConfig->Write(wxT("Width"), GetColumnWidth(iIndex));
#endif
    }


    pConfig->SetPath(strBaseConfigLocation);
    pConfig->Write(wxT("SortColumn"), m_pParentView->m_iSortColumn);
    pConfig->Write(wxT("ReverseSortOrder"), m_pParentView->m_bReverseSort);

    return true;
}
