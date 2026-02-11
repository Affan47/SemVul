RefreshLine( size_t line )
{
    if ( InReportView() )
    {
        size_t visibleFrom, visibleTo;
        GetVisibleLinesRange(&visibleFrom, &visibleTo);

        if ( line < visibleFrom || line > visibleTo )
            return;
    }

    wxRect rect = GetLineRect(line);

    CalcScrolledPosition( rect.x, rect.y, &rect.x, &rect.y );
    RefreshRect( rect );
}
