display()
{
  if (kballbmpassigned == 0)
    {
      kballbmp = load_bmp("kball.bmp");
      activebmp = load_bmp("kballa.bmp");
      kballbmpassigned = 1;
    }
  int pic;
  if (activechop)
    pic = activebmp;
  else
    pic = kballbmp;

  display_bmp(pic, int(center.x) - bmp_size(pic).x / 2,
	      int (center.y) - bmp_size(pic).y / 2);
}
