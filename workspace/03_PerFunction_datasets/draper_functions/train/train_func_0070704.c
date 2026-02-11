getFont(ustring name, ustring xftFont, bool antialias) {
#else
ref<YFont> YFont::getFont(ustring name, ustring xftFont, bool) {
#endif
    ref<YFont> font;

#if CONFIG_XFREETYPE == 1
    if (haveXft == -1) {
        int renderEvents, renderErrors;

        haveXft = (XRenderQueryExtension(xapp->display(), &renderEvents, &renderErrors) &&
                   XftDefaultHasRender(xapp->display())) ? 1 : 0;

        MSG(("RENDER extension: %d", haveXft));
        haveXft = 1;
    }
#endif

#ifdef CONFIG_XFREETYPE
#if CONFIG_XFREETYPE == 1
    if (haveXft)
#endif
    {
        if (xftFont != null && xftFont.length() > 0)
            return getXftFont(xftFont, antialias);
        else
            return getXftFontXlfd(name, antialias);
    }
#endif

#ifdef CONFIG_COREFONTS
    char tmp[4096];
    name.copy(tmp, sizeof(tmp));
    return getCoreFont(tmp);
#else
    return null;
#endif
}
