mailimap_xlist_extension_parse(int calling_parser, mailstream * fd,
                               MMAPString * buffer, size_t * indx,
                               struct mailimap_extension_data ** result,
                               size_t progr_rate, progress_function * progr_fun)
{
  int r;
  struct mailimap_mailbox_list * xlist_data = NULL;
  struct mailimap_extension_data * ext_data;
  void * data;
  int type;
  size_t cur_token;

  cur_token = * indx;

  switch (calling_parser)
  {
    case MAILIMAP_EXTENDED_PARSER_RESPONSE_DATA:
      r = mailimap_mailbox_data_xlist_parse(fd, buffer, &cur_token,
                                            &xlist_data, progr_rate, progr_fun);
      if (r == MAILIMAP_NO_ERROR) {
        type = MAILIMAP_XLIST_TYPE_XLIST;
        data = xlist_data;
      }

      if (r != MAILIMAP_NO_ERROR) {
        return r;
      }

      ext_data = mailimap_extension_data_new(&mailimap_extension_xlist,
                                             type, data);
      if (ext_data == NULL) {
        if (xlist_data != NULL)
          mailimap_mailbox_list_free(xlist_data);
        return MAILIMAP_ERROR_MEMORY;
      }

      * result = ext_data;
      * indx = cur_token;

      return MAILIMAP_NO_ERROR;

    default:


      return MAILIMAP_ERROR_PARSE;
  }
}
