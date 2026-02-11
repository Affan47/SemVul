DoGetPropertyValues( const wxString& listname,
                                                    wxPGProperty* baseparent,
                                                    long flags ) const
{
    wxPGProperty* pwc = (wxPGProperty*) baseparent;


    if ( !pwc )
        pwc = m_properties;

    wxVariantList tempList;
    wxVariant v( tempList, listname );

    if ( pwc->GetChildCount() )
    {
        if ( flags & wxPG_KEEP_STRUCTURE )
        {
            wxASSERT( !pwc->IsFlagSet(wxPG_PROP_AGGREGATE) );

            size_t i;
            for ( i=0; i<pwc->GetCount(); i++ )
            {
                wxPGProperty* p = pwc->Item(i);
                if ( !p->GetChildCount() || p->HasFlag(wxPG_PROP_AGGREGATE) )
                {
                    wxVariant variant = p->GetValue();
                    variant.SetName( p->GetBaseName() );
                    v.Append( variant );
                }
                else
                {
                    v.Append( DoGetPropertyValues(p->m_name,p,flags|wxPG_KEEP_STRUCTURE) );
                }
                if ( (flags & wxPG_INC_ATTRIBUTES) && p->m_attributes.GetCount() )
                    v.Append( p->GetAttributesAsList() );
            }
        }
        else
        {
            wxPropertyGridConstIterator it( this, wxPG_ITERATE_DEFAULT, pwc->Item(0) );
            it.SetBaseParent( pwc );

            for ( ; !it.AtEnd(); it.Next() )
            {
                const wxPGProperty* p = it.GetProperty();


                if ( !p->GetChildCount() || p->HasFlag(wxPG_PROP_AGGREGATE) )
                {
                    wxVariant variant = p->GetValue();
                    variant.SetName( p->GetName() );
                    v.Append( variant );
                    if ( (flags & wxPG_INC_ATTRIBUTES) && p->m_attributes.GetCount() )
                        v.Append( p->GetAttributesAsList() );
                }
            }
        }
    }

    return v;
}
