gui_list_io_initialize (void)
{
  eef_data_t i = 0;
  for( i = 0; i < IO_LIST_MAX_LEN && i+start <= EEF_DATA_T_MAX ; i++)
  {
    gui_list_io_add (i+start, sys.io[i + start]);
  }
}
