OnCboSearchExprEnter(wxCommandEvent &event)

{


    ThreadSearchFindData findData;
    m_ThreadSearchPlugin.GetFindData(findData);
    findData.SetFindText(m_pCboSearchExpr->GetValue());
    ThreadedSearch(findData);
}
