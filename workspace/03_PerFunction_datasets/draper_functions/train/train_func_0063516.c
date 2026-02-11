RecreateEditor()
{
    wxPropertyGrid* pg = GetGrid();
    wxASSERT(pg);

    wxPGProperty* selected = pg->GetSelection();
    if ( this == selected )
    {
        pg->DoSelectProperty(this, wxPG_SEL_FORCE);
        return true;
    }
    return false;
}
