GetBitmapFile(int button)
{
#ifndef NO_ICONS
  char *path = NULL;
  int HotX,HotY;

  path = findIconFile(Buttons[button].icon_file, iconPath,R_OK);
  if(path == NULL)return;

  if(XReadBitmapFile (dpy, Root,path,(unsigned int *)&Buttons[button].icon_w,
		      (unsigned int *)&Buttons[button].icon_h,
		      &Buttons[button].iconPixmap,
		      (int *)&HotX,
		      (int *)&HotY) != BitmapSuccess)
    {
      Buttons[button].icon_w = 0;
      Buttons[button].icon_h = 0;
    }
  else
    {
      Buttons[button].icon_depth = -1;
    }
  Buttons[button].icon_maskPixmap = None;
  free(path);
#endif
}
