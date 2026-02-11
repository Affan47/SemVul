GetIconBitmap(FvwmWindow *tmp_win)
{


  XGetGeometry(dpy, tmp_win->wmhints->icon_pixmap, &JunkRoot, &JunkX, &JunkY,
	       (unsigned int *)&tmp_win->icon_p_width,
	       (unsigned int *)&tmp_win->icon_p_height, &JunkBW, &JunkDepth);
  tmp_win->iconPixmap = tmp_win->wmhints->icon_pixmap;
  tmp_win->iconDepth = JunkDepth;
#ifdef SHAPE
  if (tmp_win->wmhints->flags & IconMaskHint)
    {
      tmp_win->flags |= SHAPED_ICON;
      tmp_win->icon_maskPixmap = tmp_win->wmhints->icon_mask;
    }
#endif
}
