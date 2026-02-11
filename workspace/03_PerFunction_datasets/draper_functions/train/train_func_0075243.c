setDecorationMask(unsigned int mask, bool apply) {
    decorations.titlebar = mask & WindowState::DECORM_TITLEBAR;
    decorations.handle   = mask & WindowState::DECORM_HANDLE;
    decorations.border   = mask & WindowState::DECORM_BORDER;
    decorations.iconify  = mask & WindowState::DECORM_ICONIFY;
    decorations.maximize = mask & WindowState::DECORM_MAXIMIZE;
    decorations.close    = mask & WindowState::DECORM_CLOSE;
    decorations.menu     = mask & WindowState::DECORM_MENU;
    decorations.sticky   = mask & WindowState::DECORM_STICKY;
    decorations.shade    = mask & WindowState::DECORM_SHADE;
    decorations.tab      = mask & WindowState::DECORM_TAB;
    decorations.enabled  = mask & WindowState::DECORM_ENABLED;


    if (apply)
        applyDecorations();
}
