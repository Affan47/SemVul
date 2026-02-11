msg_free(struct msg *tmp)
{
  if (tmp->from_name_data != NULL)
      free (tmp->from_name_data);
  if (tmp->to_name_data != NULL)
      free (tmp->to_name_data);
  if (tmp->attack_data != NULL)
      kill_free(tmp->attack_data);
  if (tmp->run_data != NULL) {
    int i;
    for (i = 0; i < tmp->run_length; ++i) {
      run_free(tmp->run_data[i]);
      tmp->run_data[i] = NULL;
    }
    free(tmp->run_data);
    tmp->run_data = NULL;
    tmp->run_length = 0;
    tmp->run_num_allocated = 0;
  }
  free(tmp);
}
