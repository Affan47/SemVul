ddjvu_map_point(ddjvu_rectmapper_t *mapper, int *x, int *y)
{
  GRectMapper *gmapper = (GRectMapper*)mapper;
  if (! gmapper) return;
  gmapper->map(*x,*y);
}
