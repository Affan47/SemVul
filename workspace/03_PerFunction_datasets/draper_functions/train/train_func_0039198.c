xsh_grid_point_compare(const void* one, const void* two){
  xsh_grid_point** a = NULL;
  xsh_grid_point** b = NULL;
  int xa, ya, xb, yb;

  a = (xsh_grid_point**) one;
  b = (xsh_grid_point**) two;

  xa = (*a)->x;
  xb = (*b)->x;

  ya = (*a)->y;
  yb = (*b)->y;

  if (ya < yb)
    return -1;
  else if ( (ya == yb) && (xa <= xb) ){
    return -1;
  }
  else{
    return 1;
  }
}
