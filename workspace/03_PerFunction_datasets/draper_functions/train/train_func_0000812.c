_delete_records (ipmi_sel_state_data_t *state_data)
{
  struct ipmi_sel_arguments *args;
  unsigned int i;

  assert (state_data);

  args = state_data->prog_data->args;

  for (i = 0; i < args->delete_record_list_length; i++)
    {
      if (_delete_entry (state_data,
                         args->delete_record_list[i],
                         0) < 0)
        return (-1);
    }

  return (0);
}
