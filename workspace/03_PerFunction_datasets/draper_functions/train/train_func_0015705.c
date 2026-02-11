ColourToString( const wxColour& col, int index ) const
{
    if ( index == wxNOT_FOUND )
        return wxString::Format(wxT("(%i,%i,%i)"),
                                (int)col.Red(),
                                (int)col.Green(),
                                (int)col.Blue());
    else
        return m_choices.GetLabel(index);
}
