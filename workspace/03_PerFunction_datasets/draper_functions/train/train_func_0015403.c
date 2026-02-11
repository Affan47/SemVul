stackfilt_init(const char *args)
{

  int invalid = 0;

  if (nowarn) {
    warnings_enabled = 0;
  }

  if (opt_depth) {
    swapdepth = atoi(opt_depth);
  }
  if (opt_push) {
    if (opt_pop || opt_append || opt_discard || opt_replace ||
        opt_swap || opt_depth) {
      invalid = 1;
    }
  } else if (opt_pop) {
    if (opt_push || opt_copy || opt_swap || opt_depth) {
      invalid = 1;
    }
    if (!!opt_append + !!opt_discard + !!opt_replace > 1) {
      invalid = 1;
    }
  } else if (opt_swap) {
    if (opt_push || opt_copy  || opt_pop || opt_append ||
        opt_discard || opt_replace) {
      invalid = 1;
    }
  } else {
    invalid = 1;
  }

  if (invalid) {
    fatal(MYNAME ": invalid combination of options\n");
  }

}
