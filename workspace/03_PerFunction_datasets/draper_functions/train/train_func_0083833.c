OnCustomEditClick(wxCommandEvent& )
{
    wxASSERT( m_pCallingClass );
    wxString str = m_edValue->GetValue();
    if ( m_pCallingClass->OnCustomStringEdit(m_parent,str) )
    {

        m_lbStrings->Append ( str );
        m_array.Add ( str );
        m_modified = true;
    }
}
