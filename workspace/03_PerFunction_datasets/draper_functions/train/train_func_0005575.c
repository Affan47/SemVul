clone_last(SEL_ARG *arg)
  {
    return new SEL_ARG(field, part, min_value, arg->max_value,
		       min_flag, arg->max_flag, maybe_flag | arg->maybe_flag);
  }
