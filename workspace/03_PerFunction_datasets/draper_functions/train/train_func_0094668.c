DrawValue( wxDC& dc, const wxRect& rect, wxPGProperty* property, const wxString& text ) const
{
    if ( !property->IsValueUnspecified() )
        dc.DrawText( text, rect.x+wxPG_XBEFORETEXT, rect.y );
}
