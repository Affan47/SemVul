mapicons(void)
{
  struct icon_info *tmp;
  tmp = Head;

  while(tmp != NULL){
    if (window_cond(tmp)){
      XMapWindow(dpy, tmp->IconWin);
      if (max_icon_height != 0)
	XMapWindow(dpy, tmp->icon_pixmap_w);
    }
    tmp = tmp->next;
  }
}
