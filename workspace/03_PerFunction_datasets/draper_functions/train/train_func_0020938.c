ExpandIconTitle (TwmWindow *tmp_win)
{
    Icon	*icon;
    XRectangle	rect;

    if (!tmp_win || !tmp_win->icon) return;
    icon = tmp_win->icon;
    if (!icon->has_title) return;
    if (icon->w_width == icon->width) return;
    if (icon->height  == 0) return;

    rect.x      = 0;
    rect.y      = icon->height;
    rect.width  = icon->w_width;
    rect.height = icon->w_height - icon->height;
    XShapeCombineRectangles (dpy, icon->w, ShapeBounding, 0, 0, &rect, 1, ShapeUnion, 0);
    icon->title_shrunk = False;
    XClearArea (dpy, icon->w, 0, icon->height, icon->w_width,
		icon->w_height - icon->height, True);
}
