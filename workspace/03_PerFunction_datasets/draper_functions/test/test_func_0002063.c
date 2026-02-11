add_hardness (int sprite, int num)
{
  int xx;
  for (xx = spr[sprite].x + k[getpic(sprite)].hardbox.left; xx < spr[sprite].x + k[getpic(sprite)].hardbox.right; xx++)
    {
      int yy;
      for (yy = spr[sprite].y + k[getpic(sprite)].hardbox.top; yy < spr[sprite].y + k[getpic(sprite)].hardbox.bottom; yy++)
	{
	  if ( (xx-20 > 600) | (xx-20 < 0)| (yy > 400) | (yy < 0))
	    ;
	  else
	    hm.x[xx-20].y[yy] = num;
	}
    }
}
