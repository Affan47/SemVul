imageinfo_lua_num_of_recmaps(lua_State *L)
{
  GtImageInfo **ii;
  unsigned long nof_rm;
  GtError *err = NULL;
  ii = check_imageinfo(L, 1);
  gt_assert(ii);
  nof_rm = gt_image_info_num_of_rec_maps(*ii);
  if (nof_rm > DBL_MAX)
  {
    err = gt_error_new();
    gt_error_set(err, "number of recmaps exceeds %f!", DBL_MAX);
    return gt_lua_error(L, err);
  }
  else
    lua_pushnumber(L, (double) nof_rm);
  gt_error_delete(err);
  return 0;
}
