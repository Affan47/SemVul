OnMoveDirDownClick(cb_unused wxSpinEvent& event)
{
    wxListBox* lst = GetDirsListBox();
    wxArrayInt sels;
    if (!lst || lst->GetSelections(sels) < 1)
        return;


    for (size_t i=lst->GetCount()-1; i>0; --i)
    {


        if (lst->IsSelected(i-1) && !lst->IsSelected(i))
        {
            wxString dir = lst->GetString(i-1);
            lst->Delete(i-1);

            lst->InsertItems(1, &dir, i);
            lst->SetSelection(i);

            m_bDirty = true;
        }
    }
}
