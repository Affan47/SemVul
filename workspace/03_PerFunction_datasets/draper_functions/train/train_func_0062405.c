register_stock_icons (AnjutaPlugin *plugin)
{
    static gboolean registered = FALSE;

    if (registered)
        return;
    registered = TRUE;


    BEGIN_REGISTER_ICON (plugin);
    REGISTER_ICON_FULL (ANJUTA_PIXMAP_SWAP, ANJUTA_STOCK_SWAP);
    REGISTER_ICON_FULL (ANJUTA_PIXMAP_AUTOINDENT, ANJUTA_STOCK_AUTOINDENT);
    END_REGISTER_ICON;
}
