parser_convert (struct parser *parser, const struct argp *argp, int flags)
{
  struct parser_convert_state cvt;

  cvt.parser = parser;
  cvt.short_end = parser->short_opts;
  cvt.long_end = parser->long_opts;
  cvt.child_inputs_end = parser->child_inputs;

  if (flags & ARGP_IN_ORDER)
    *cvt.short_end++ = '-';
  else if (flags & ARGP_NO_ARGS)
    *cvt.short_end++ = '+';
  *cvt.short_end = '\0';

  cvt.long_end->name = NULL;

  parser->argp = argp;

  if (argp)
    parser->egroup = convert_options (argp, 0, 0, parser->groups, &cvt);
  else
    parser->egroup = parser->groups;
}
