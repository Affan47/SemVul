setTooltipColumns( bool columns[] )
{
    for( int i=0; i<Playlist::NUM_COLUMNS; ++i )
        s_tooltipColumns[i] = columns[i];
}
