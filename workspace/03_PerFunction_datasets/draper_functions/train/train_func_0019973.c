setShowVertScrollbar(bool mode)
{
    if (mode != d_forceVScroll)
    {
        d_forceVScroll = mode;
        WindowEventArgs e(this);
        onVertScrollbarModeChanged(e);
    }
}
