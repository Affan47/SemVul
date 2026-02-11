router_have_minimum_dir_info(void)
{
  if (PREDICT_UNLIKELY(need_to_update_have_min_dir_info)) {
    update_router_have_minimum_dir_info();
    need_to_update_have_min_dir_info = 0;
  }
  return have_min_dir_info;
}
