init(NPWindow* aWindow)
{
    if(!aWindow) {
        gnash::log_error("%s: ERROR: Window handle was bogus!", __PRETTY_FUNCTION__);
        return FALSE;
    } else {
#if GNASH_PLUGIN_DEBUG > 1
        std::cout << "X origin: = " << aWindow->x
            << ", Y Origin = " << aWindow->y
            << ", Width = " << aWindow->width
            << ", Height = " << aWindow->height
            << ", WindowID = " << aWindow->window
            << ", this = " << static_cast<void*>(this) << std::endl;
#endif
    }

    return TRUE;
}
