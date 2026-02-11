OnEvent( wxPropertyGrid* propGrid,
                                     wxWindow* primary,
                                     wxEvent& event )
{
    if ( propGrid->IsMainButtonEvent(event) )
        return OnButtonClick(propGrid,primary,(const wxChar*) NULL);
    return false;
}
