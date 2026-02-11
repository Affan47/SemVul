get_file_options_ulllist(char *&ptr, char *end, char *line,
                              uchar* base, File_option *parameter,
                              MEM_ROOT *mem_root)
{
  List<ulonglong> *nlist= (List<ulonglong>*)(base + parameter->offset);
  ulonglong *num;
  nlist->empty();

  while (ptr < end)
  {
    int not_used;
    char *num_end= end;
    if (!(num= (ulonglong*)alloc_root(mem_root, sizeof(ulonglong))) ||
        nlist->push_back(num, mem_root))
      goto nlist_err;
    *num= my_strtoll10(ptr, &num_end, &not_used);
    ptr= num_end;
    switch (*ptr) {
    case '\n':
      goto end_of_nlist;
    case ' ':

      ptr++;
      break;
    default:
      goto nlist_err_w_message;
    }
  }

end_of_nlist:
  if (*(ptr++) != '\n')
    goto nlist_err;
  return FALSE;

nlist_err_w_message:
  my_error(ER_FPARSER_ERROR_IN_PARAMETER, MYF(0), parameter->name.str, line);
nlist_err:
  return TRUE;
}
