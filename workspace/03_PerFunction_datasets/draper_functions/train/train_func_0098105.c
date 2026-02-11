SetPropertyLabel( wxPGPropArg id, const wxString& newproplabel )
{
    wxPG_PROP_ARG_CALL_PROLOG()

    p->SetLabel( newproplabel );

    wxPropertyGridState* state = p->GetParentState();
    wxPropertyGrid* pg = state->GetGrid();

    if ( pg->HasFlag(wxPG_AUTO_SORT) )
        pg->Sort(p->GetParent());

    if ( pg->GetState() == state )
    {
        if ( pg->HasFlag(wxPG_AUTO_SORT) )
            pg->Refresh();
        else
            pg->DrawItem( p );
    }
}
