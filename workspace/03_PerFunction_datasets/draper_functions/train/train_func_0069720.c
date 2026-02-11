OnArrowChar(size_t newCurrent, const wxKeyEvent& event)
{
    wxCHECK_RET( newCurrent < (size_t)GetItemCount(),
                 _T("invalid item index in OnArrowChar()") );

    size_t oldCurrent = m_current;


    if ( event.ShiftDown() && !IsSingleSel() )
    {
        ChangeCurrent(newCurrent);


        RefreshLine( oldCurrent );


        if ( oldCurrent > newCurrent )
        {
            newCurrent = oldCurrent;
            oldCurrent = m_current;
        }

        HighlightLines(oldCurrent, newCurrent);
    }
    else
    {


        if ( !event.ControlDown() || IsSingleSel() )
            HighlightAll(false);

        ChangeCurrent(newCurrent);


        RefreshLine( oldCurrent );


        if ( !event.ControlDown() || IsSingleSel() )
            HighlightLine( m_current, true );
    }

    RefreshLine( m_current );

    MoveToFocus();
}
