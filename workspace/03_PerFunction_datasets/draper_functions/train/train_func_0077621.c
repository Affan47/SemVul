gui_widget_apply_wallpaper(
    GuiWidget *widget, SDL_Surface *wallpaper, int alpha )
{
    if ( widget->parent )
        stk_surface_blit( widget->parent->surface,
                          widget->parent_region.x +
                          widget->border,
                          widget->parent_region.y +
                          widget->border,
                          widget->parent_region.w -
                          (widget->border<<1),
                          widget->parent_region.h -
                          (widget->border<<1),
                          widget->surface,
                          widget->border, widget->border );
    else
        stk_surface_apply_wallpaper(
            widget->surface, widget->border, widget->border,
            widget->parent_region.w - (widget->border<<1),
            widget->parent_region.h - (widget->border<<1),
            wallpaper, alpha );
}
