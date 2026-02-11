set_label(const char *status_arg,
                                 const char *function_arg,
                                 const char *file_arg, unsigned int line_arg)
{
  size_t sizes[3];
  char *cursor;


  sizes[0]= (status_arg == NULL) ? 0 : strlen(status_arg) + 1;
  sizes[1]= (function_arg == NULL) ? 0 : strlen(function_arg) + 1;
  sizes[2]= (file_arg == NULL) ? 0 : strlen(file_arg) + 1;

  allocated_status_memory= (char *) my_malloc(sizes[0] + sizes[1] + sizes[2], MYF(0));
  DBUG_ASSERT(allocated_status_memory != NULL);

  cursor= allocated_status_memory;

  if (status_arg != NULL)
  {
    strcpy(cursor, status_arg);
    status= cursor;
    cursor+= sizes[0];
  }
  else
    status= NULL;

  if (function_arg != NULL)
  {
    strcpy(cursor, function_arg);
    function= cursor;
    cursor+= sizes[1];
  }
  else
    function= NULL;

  if (file_arg != NULL)
  {
    strcpy(cursor, file_arg);
    file= cursor;
    cursor+= sizes[2];
  }
  else
    file= NULL;

  line= line_arg;
}
