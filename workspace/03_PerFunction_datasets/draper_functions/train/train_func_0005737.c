do_encoding (struct _IO_codecvt *codecvt)
{
#ifdef _LIBC

  if (codecvt->__cd_in.__cd.__steps[0].__stateful)
    return -1;


  if (codecvt->__cd_in.__cd.__steps[0].__min_needed_from
      != codecvt->__cd_in.__cd.__steps[0].__max_needed_from)

    return 0;

  return codecvt->__cd_in.__cd.__steps[0].__min_needed_from;
#else

  return -1;
#endif
}
