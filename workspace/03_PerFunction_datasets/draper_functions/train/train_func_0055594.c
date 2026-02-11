Scroll(int Desk, int x, int y)
{
#ifndef NON_VIRTUAL
  char command[256];
  int sx, sy;
  if(Wait == 0)
    {
      if(Desk != Scr.CurrentDesk)
	{
	  return;
	}

      if(x < 0)
	x = 0;
      if(y < 0)
	y = 0;

      if(x > desk_w)
	x = desk_w;
      if(y > desk_h)
	y = desk_h;

      sx = (100*(x*(Scr.VxMax+Scr.MyDisplayWidth)/desk_w- Scr.Vx))/Scr.MyDisplayWidth;
      sy = (100*(y*(Scr.VyMax+Scr.MyDisplayHeight)/
		   desk_h - Scr.Vy))/Scr.MyDisplayHeight;
      if(sx > 100)sx = 100;
      if(sx < -100)sx = -100;
      if(sy < -100)sy = -100;
      if(sy > 100)sy = 100;

      sprintf(command,"Scroll %d %d\n",sx,sy);
      SendInfo(fd,command,0);
      Wait = 1;
    }
#endif
}
