SetItemStateAll(long state, long stateMask)
{
    if ( IsEmpty() )
        return;


    if ( stateMask & wxLIST_STATE_SELECTED )
    {

        if ( IsVirtual() )
        {

            m_selStore.SelectRange(0, GetItemCount() - 1, state == wxLIST_STATE_SELECTED);
            Refresh();
        }
        else if ( state & wxLIST_STATE_SELECTED )
        {
            const long count = GetItemCount();
            for( long i = 0; i <  count; i++ )
            {
                SetItemState( i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED );
            }

        }
        else
        {

            long i = -1;
            while ( (i = GetNextItem(i, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != -1 )
            {
                SetItemState( i, 0, wxLIST_STATE_SELECTED );
            }
        }
    }

    if ( HasCurrent() && (state == 0) && (stateMask & wxLIST_STATE_FOCUSED) )
    {


        SetItemState(m_current, state, stateMask);
    }

}
