box_bounds (GfsBox * box, LocateArray * a)
{
  root_bounds (box->root, a);
  FttDirection d;
  for (d = 0; d < FTT_NEIGHBORS; d++)
    if (GFS_IS_BOUNDARY (box->neighbor[d]))
      root_bounds (GFS_BOUNDARY (box->neighbor[d])->root, a);
}
