unix_setsockopt_aux(char * name,
                    enum option_type ty, int level, int option,
                    value socket, value val)
{
  union option_value optval;
  socklen_param_type optsize;
  double f;

  switch (ty) {
  case TYPE_BOOL:
  case TYPE_INT:
    optsize = sizeof(optval.i);
    optval.i = Int_val(val);
    break;
  case TYPE_LINGER:
    optsize = sizeof(optval.lg);
    optval.lg.l_onoff = Is_block (val);
    if (optval.lg.l_onoff)
      optval.lg.l_linger = Int_val (Field (val, 0));
    break;
  case TYPE_TIMEVAL:
    f = Double_val(val);
    optsize = sizeof(optval.tv);
    optval.tv.tv_sec = (int) f;
    optval.tv.tv_usec = (int) (1e6 * (f - optval.tv.tv_sec));
    break;
  case TYPE_UNIX_ERROR:
  default:
    unix_error(EINVAL, name, Nothing);
  }

  if (setsockopt(Int_val(socket), level, option,
                 (void *) &optval, optsize) == -1)
    uerror(name, Nothing);

  return Val_unit;
}
