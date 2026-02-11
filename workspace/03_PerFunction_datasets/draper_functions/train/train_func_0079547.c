get_dump_file_info (int phase)
{
  if (phase < TDI_end)
    return &dump_files[phase];
  else if ((size_t) (phase - TDI_end) >= extra_dump_files_in_use)
    return NULL;
  else
    return extra_dump_files + (phase - TDI_end);
}
