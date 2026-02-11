GetPropertyByLabel( const wxString& label,
                                                         wxPropertyGridState** ppState ) const
{
    size_t i;
    for ( i=0; i<GetPageCount(); i++ )
    {
        wxPropertyGridState* pState = ((wxPropertyGridPage*)m_arrPages.Item(i))->GetStatePtr();
        wxPGProperty* p = pState->GetPropertyByLabel(label);
        if ( p )
        {
            if ( ppState ) *ppState = pState;
            return p;
        }
    }
    return NULL;
}
