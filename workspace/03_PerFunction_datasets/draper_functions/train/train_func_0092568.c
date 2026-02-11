unix_getsockopt_aux(char * name,
                    enum option_type ty, int level, int option,
                    value socket)
{
  union option_value optval;
  socklen_param_type optsize;


  switch (ty) {
  case TYPE_BOOL:
  case TYPE_INT:
  case TYPE_UNIX_ERROR:
    optsize = sizeof(optval.i); break;
  case TYPE_LINGER:
    optsize = sizeof(optval.lg); break;
  case TYPE_TIMEVAL:
    optsize = sizeof(optval.tv); break;
  default:
    unix_error(EINVAL, name, Nothing);
  }

  if (getsockopt(Int_val(socket), level, option,
                 (void *) &optval, &optsize) == -1)
    uerror(name, Nothing);

  switch (ty) {
  case TYPE_BOOL:
  case TYPE_INT:
    return Val_int(optval.i);
  case TYPE_LINGER:
    if (optval.lg.l_onoff == 0) {
      return Val_int(0);
    } else {
      value res = alloc_small(1, 0);
      Field(res, 0) = Val_int(optval.lg.l_linger);
      return res;
    }
  case TYPE_TIMEVAL:
    return copy_double((double) optval.tv.tv_sec
                       + (double) optval.tv.tv_usec / 1e6);
  case TYPE_UNIX_ERROR:
    if (optval.i == 0) {
      return Val_int(0);
    } else {
      value err, res;
      err = unix_error_of_code(optval.i);
      Begin_root(err);
        res = alloc_small(1, 0);
        Field(res, 0) = err;
      End_roots();
      return res;
    }
  default:
    unix_error(EINVAL, name, Nothing);
  }
}
