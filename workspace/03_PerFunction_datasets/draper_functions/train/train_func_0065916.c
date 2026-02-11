FetchWmColormapWindows (FvwmWindow *tmp)
{
  if(tmp->cmap_windows != (Window *)NULL)
    XFree((void *)tmp->cmap_windows);

  if(!XGetWMColormapWindows (dpy, tmp->w, &(tmp->cmap_windows),
			     &(tmp->number_cmap_windows)))
    {
      tmp->number_cmap_windows = 0;
      tmp->cmap_windows = NULL;
    }
}
