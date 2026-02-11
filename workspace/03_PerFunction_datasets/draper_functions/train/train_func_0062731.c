HasVisibleChildren() const
{
    unsigned int i;

    for ( i=0; i<GetChildCount(); i++ )
    {
        wxPGProperty* child = Item(i);

        if ( !child->HasFlag(wxPG_PROP_HIDDEN) )
            return true;
    }

    return false;
}
