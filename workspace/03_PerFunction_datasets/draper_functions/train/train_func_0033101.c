WI_drawPercent
( int		x,
  int		y,
  int		p )
{
    if (p < 0)
	return;

    V_DrawPatch(x, y, percent);
    WI_drawNum(x, y, p, -1);
}
