ClearModifiedStatus( wxPGPropArg id )
{
    wxPG_PROP_ARG_CALL_PROLOG()

    wxPropertyGridState* pState = p->GetParentState();
    wxASSERT ( pState != (wxPropertyGridState*) NULL );
    pState->ClearModifiedStatus(p);
}
