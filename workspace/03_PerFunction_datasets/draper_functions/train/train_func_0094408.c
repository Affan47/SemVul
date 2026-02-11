setExtendedStrut( WId win, int left_width, int left_start, int left_end,
    int right_width, int right_start, int right_end, int top_width, int top_start, int top_end,
    int bottom_width, int bottom_start, int bottom_end )
{
    NETWinInfo info( QX11Info::display(), win, QX11Info::appRootWindow(), 0 );
    NETExtendedStrut strut;
    strut.left_width = left_width;
    strut.right_width = right_width;
    strut.top_width = top_width;
    strut.bottom_width = bottom_width;
    strut.left_start = left_start;
    strut.left_end = left_end;
    strut.right_start = right_start;
    strut.right_end = right_end;
    strut.top_start = top_start;
    strut.top_end = top_end;
    strut.bottom_start = bottom_start;
    strut.bottom_end = bottom_end;
    info.setExtendedStrut( strut );
    NETStrut oldstrut;
    oldstrut.left = left_width;
    oldstrut.right = right_width;
    oldstrut.top = top_width;
    oldstrut.bottom = bottom_width;
    info.setStrut( oldstrut );
}
