find_custom_fold_func (gpointer item, GValue * ret, FindCustomFoldData * data)
{
  if (data->func (item, data->user_data) == 0) {
    g_value_set_pointer (ret, item);
    return FALSE;
  } else {
    return TRUE;
  }
}
