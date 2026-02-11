mailimf_reply_to_write_driver(int (* do_write)(void *, const char *, size_t), void * data, int * col,
				  struct mailimf_reply_to * reply_to)
{
  int r;

  r = mailimf_string_write_driver(do_write, data, col, "Reply-To: ", 10);
  if (r != MAILIMF_NO_ERROR)
    return r;

  r = mailimf_address_list_write_driver(do_write, data, col, reply_to->rt_addr_list);
  if (r != MAILIMF_NO_ERROR)
    return r;

  r = mailimf_string_write_driver(do_write, data, col, "\r\n", 2);
  if (r != MAILIMF_NO_ERROR)
    return r;
#if 0
  * col = 0;
#endif

  return MAILIMF_NO_ERROR;
}
