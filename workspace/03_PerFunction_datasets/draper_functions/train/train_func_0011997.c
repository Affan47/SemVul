compare(const char *log_file_name1, my_off_t log_file_pos1,
			 const char *log_file_name2, my_off_t log_file_pos2)
{
  int cmp = strcmp(log_file_name1, log_file_name2);

  if (cmp != 0)
    return cmp;

  if (log_file_pos1 > log_file_pos2)
    return 1;
  else if (log_file_pos1 < log_file_pos2)
    return -1;
  return 0;
}
