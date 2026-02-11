GetCompilerIndex(const wxString& id)
{
    const wxString lid = id.Lower();
    for (size_t i = 0; i < Compilers.GetCount(); ++i)
    {
        if (Compilers[i]->GetID().IsSameAs(lid))
            return i;
    }

    for (size_t i = 0; i < Compilers.GetCount(); ++i)
    {
        wxString oldId = Compilers[i]->GetID();
        oldId.Replace(wxT("-"), wxEmptyString);
        if (oldId.IsSameAs(lid))
            return i;
    }
    return -1;
}
