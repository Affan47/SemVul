GetSelectedItemCount() const
{

    if ( IsSingleSel() )
        return HasCurrent() ? IsHighlighted(m_current) : false;


    if ( IsVirtual() )
        return m_selStore.GetSelectedCount();


    size_t countSel = 0;
    size_t count = GetItemCount();
    for ( size_t line = 0; line < count; line++ )
    {
        if ( GetLine(line)->IsHighlighted() )
            countSel++;
    }

    return countSel;
}
