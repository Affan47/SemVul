SetTextColourIndex( wxPGProperty* p, int index,
                                         int flags )
{
    unsigned char ind = index;

    p->m_fgColIndex = ind;

    if ( flags & wxPG_RECURSE )
    {
        unsigned int i;
        for ( i=0; i<p->GetChildCount(); i++ )
            SetTextColourIndex( p->Item(i), index, flags );
    }
}
