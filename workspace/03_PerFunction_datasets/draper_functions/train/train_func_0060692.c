GetDefaultRendererForType(const wxString& typeName) const
{
    int index = GetSheetRefData()->m_typeRegistry->FindOrCloneDataType(typeName);
    wxCHECK_MSG(index != wxNOT_FOUND, wxNullSheetCellRenderer, wxT("Unknown data type name"));

    return GetSheetRefData()->m_typeRegistry->GetRenderer(index);
}
