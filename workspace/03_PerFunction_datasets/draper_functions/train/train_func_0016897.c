GetSearch() const
{
  wxString search(_T(""));

  if (txtSearch)
    search = txtSearch->GetValue();

  return search;
}
