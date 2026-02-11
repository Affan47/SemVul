do_menu (MenuRoot *menu)
{
  int prevStashedX=0,prevStashedY=0;
  MenuRoot *PrevActiveMenu=0;
  MenuItem *PrevActiveItem=0;
  int retval=MENU_NOP;
  int x,y;


  if(menu->in_use)
    return MENU_ERROR;


  XQueryPointer( dpy, Scr.Root, &JunkRoot, &JunkChild,
		&x, &y, &JunkX, &JunkY, &JunkMask);

  if(menu_on)
    {
      prevStashedX = Stashed_X;
      prevStashedY = Stashed_Y;

      PrevActiveMenu = ActiveMenu;
      PrevActiveItem = ActiveItem;
      if(ActiveMenu)
	if(Scr.flags & MWMMenus)
	  x = Stashed_X+ (ActiveMenu->width >> 1) + (menu->width >> 1) - 3;
      if(ActiveItem)
	y = ActiveItem->y_offset + MenuY + (Scr.EntryHeight >>1);
    }
  else
    {
      if(!GrabEm(MENU))
	{
	  XBell(dpy,Scr.screen);
	  return MENU_DONE;
	}
      if(Scr.flags & MWMMenus)
	x += (menu->width >> 1) - 3;
    }
  if (PopUpMenu (menu, x, y))
    {
      retval = UpdateMenu();
    }
  else
    XBell (dpy, Scr.screen);

  ActiveMenu = PrevActiveMenu;
  ActiveItem = PrevActiveItem;
  if((ActiveItem)&&(menu_on))
    ActiveItem->state = 1;
  Stashed_X = prevStashedX;
  Stashed_Y = prevStashedY;


  if(!menu_on)
    {
      UngrabEm();
      WaitForButtonsUp();
    }
  return retval;
}
