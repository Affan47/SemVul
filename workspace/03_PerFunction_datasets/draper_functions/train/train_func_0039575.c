argp_doc (const struct argp *argp, const struct argp_state *state,
	  int post, int pre_blank, int first_only,
	  argp_fmtstream_t stream)
{
  const char *text;
  const char *inp_text;
  void *input = 0;
  int anything = 0;
  size_t inp_text_limit = 0;
  const char *doc = dgettext (argp->argp_domain, argp->doc);
  const struct argp_child *child = argp->children;

  if (doc)
    {
      char *vt = strchr (doc, '\v');
      inp_text = post ? (vt ? vt + 1 : 0) : doc;
      inp_text_limit = (!post && vt) ? (vt - doc) : 0;
    }
  else
    inp_text = 0;

  if (argp->help_filter)

    {
      if (inp_text_limit)

	inp_text = STRNDUP (inp_text, inp_text_limit);
      input = __argp_input (argp, state);
      text =
	(*argp->help_filter) (post
			      ? ARGP_KEY_HELP_POST_DOC
			      : ARGP_KEY_HELP_PRE_DOC,
			      inp_text, input);
    }
  else
    text = (const char *) inp_text;

  if (text)
    {
      if (pre_blank)
	__argp_fmtstream_putc (stream, '\n');

      if (text == inp_text && inp_text_limit)
	__argp_fmtstream_write (stream, inp_text, inp_text_limit);
      else
	__argp_fmtstream_puts (stream, text);

      if (__argp_fmtstream_point (stream) > __argp_fmtstream_lmargin (stream))
	__argp_fmtstream_putc (stream, '\n');

      anything = 1;
    }

  if (text && text != inp_text)
    free ((char *) text);
  if (inp_text && inp_text_limit && argp->help_filter)
    free ((char *) inp_text);

  if (post && argp->help_filter)

    {
      text = (*argp->help_filter) (ARGP_KEY_HELP_EXTRA, 0, input);
      if (text)
	{
	  if (anything || pre_blank)
	    __argp_fmtstream_putc (stream, '\n');
	  __argp_fmtstream_puts (stream, text);
	  free ((char *) text);
	  if (__argp_fmtstream_point (stream)
	      > __argp_fmtstream_lmargin (stream))
	    __argp_fmtstream_putc (stream, '\n');
	  anything = 1;
	}
    }

  if (child)
    while (child->argp && !(first_only && anything))
      anything |=
	argp_doc ((child++)->argp, state,
		  post, anything || pre_blank, first_only,
		  stream);

  return anything;
}
