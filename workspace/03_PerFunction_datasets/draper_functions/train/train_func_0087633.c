fill_elinfo(int ichild, const EL_INFO *parent_info, EL_INFO *elinfo)
{
  FUNCNAME("fill_elinfo");
  int dim = parent_info->mesh->dim;

  switch(dim) {
  case 1:
    fill_elinfo_1d(ichild, parent_info, elinfo);
    break;
#if DIM_OF_WORLD > 1
  case 2:
    fill_elinfo_2d(ichild, parent_info, elinfo);
    break;
#if DIM_OF_WORLD > 2
  case 3:
    fill_elinfo_3d(ichild, parent_info, elinfo);
    break;
#endif
#endif
  default:
    ERROR_EXIT("Illegal dim == %d!\n", dim);
  }
}
