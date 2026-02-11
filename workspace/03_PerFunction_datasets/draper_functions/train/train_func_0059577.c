EndAddChildren( wxPGPropArg id )
{
    wxPG_PROP_ARG_CALL_PROLOG()
    wxCHECK_RET( p->HasFlag(wxPG_PROP_MISC_PARENT), wxT("only call on properties for which BeginAddChildren was called prior") );
    p->ClearFlag(wxPG_PROP_MISC_PARENT);
    p->SetFlag(wxPG_PROP_AGGREGATE);
}
