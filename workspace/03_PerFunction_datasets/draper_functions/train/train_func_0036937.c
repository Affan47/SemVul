GetMonitorRect(Point pt)
{
    wxRect rect;
    if (! wid) return PRectangle();
#if wxUSE_DISPLAY

    int n = wxDisplay::GetFromPoint(wxPoint(pt.x, pt.y));
    wxDisplay dpy(n == wxNOT_FOUND ? 0 : n);
    rect = dpy.GetGeometry();
#else
    wxUnusedVar(pt);
#endif
    return PRectangleFromwxRect(rect);
}
