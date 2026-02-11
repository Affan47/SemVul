res_thread_freeres (void)
{
  if (_res.nscount == 0)

    return;

  __res_iclose (&_res, true);


  _res.options = 0;
}
