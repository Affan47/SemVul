EndModal(int retCode)
{
    if (retCode == wxID_OK)
    {
        wxListBox* list = XRCCTRL(*this, "lstItems", wxListBox);
        m_Array.Clear();
        for (int i = 0; i < (int)list->GetCount(); ++i)
        {
            m_Array.Add(list->GetString(i));
        }
    }
    wxScrollingDialog::EndModal(retCode);
}
