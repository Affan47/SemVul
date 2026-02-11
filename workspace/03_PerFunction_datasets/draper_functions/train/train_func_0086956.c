mailimap_struct_multiple_parse_progress(mailstream * fd, MMAPString * buffer,
                                        size_t * indx, clist ** result,
                                        mailimap_struct_parser_progress * parser,
                                        mailimap_struct_destructor * destructor,
                                        size_t progr_rate,
                                        progress_function * progr_fun,
                                        mailprogress_function * body_progr_fun,
                                        mailprogress_function * items_progr_fun,
                                        void * context)
{
  clist * struct_list;
  size_t cur_token;
  void * value;
  int r;
  int res;

  cur_token = * indx;

  r = parser(fd, buffer, &cur_token, &value, progr_rate, progr_fun,
             body_progr_fun, items_progr_fun, context);
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    goto err;
  }

  struct_list = clist_new();
  if (struct_list == NULL) {
    destructor(value);
    res = MAILIMAP_ERROR_MEMORY;
    goto err;
  }

  r = clist_append(struct_list, value);
  if (r < 0) {
    destructor(value);
    res = MAILIMAP_ERROR_MEMORY;
    goto free_list;
  }

  while (1) {
    r = parser(fd, buffer, &cur_token, &value, progr_rate, progr_fun,
               body_progr_fun, items_progr_fun, context);
    if (r == MAILIMAP_ERROR_PARSE)
      break;
    if (r != MAILIMAP_NO_ERROR) {
      res = r;
      goto free_list;
    }

    r = clist_append(struct_list, value);
    if (r < 0) {
      destructor(value);
      res = MAILIMAP_ERROR_MEMORY;
      goto free_list;
    }
  }

  * result = struct_list;
  * indx = cur_token;

  return MAILIMAP_NO_ERROR;

free_list:
  clist_foreach(struct_list, (clist_func) destructor, NULL);
  clist_free(struct_list);
err:
  return res;
}
