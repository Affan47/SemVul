sorted_wall_indices(const int dim, int wall, int permno)
{
  FUNCNAME("wall_orientation");

  switch(dim) {
  case 0:
    WARNING("Does not makes sense for dim == 0!\n");
    break;
  case 1:
    return sorted_wall_indices_1d(wall, permno);
    break;
#if DIM_OF_WORLD > 1
  case 2:
    return sorted_wall_indices_2d(wall, permno);
    break;
#if DIM_OF_WORLD > 2
  case 3:
    return sorted_wall_indices_3d(wall, permno);
    break;
#endif
#endif
  default:
    ERROR_EXIT("Illegal dim!\n");
  }

  return nil;
}
