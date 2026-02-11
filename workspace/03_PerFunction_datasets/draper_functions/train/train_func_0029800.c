set_manager_window_mapping(WinManager *man, int flag)
{
  if (flag != man->window_mapped) {
    man->window_mapped = flag;
    man->dirty_flags |= MAPPING_CHANGED;
  }
}
