clip_value (const SANE_Option_Descriptor * opt, void * value)
{
  const SANE_String_Const * string_list;
  const SANE_Word * word_list;
  int i, num_matches, match;
  const SANE_Range * range;
  SANE_Word w, v;
  size_t len;

  switch (opt->constraint_type)
    {
    case SANE_CONSTRAINT_RANGE:
      w = *(SANE_Word *) value;
      range = opt->constraint.range;

      if (w < range->min)
        w = range->min;
      else if (w > range->max)
	w = range->max;

      if (range->quant)
	{
	  v = (w - range->min + range->quant/2) / range->quant;
	  w = v * range->quant + range->min;
	  *(SANE_Word*) value = w;
	}
      break;

    case SANE_CONSTRAINT_WORD_LIST:
      w = *(SANE_Word *) value;
      word_list = opt->constraint.word_list;
      for (i = 1; w != word_list[i]; ++i)
	if (i >= word_list[0])


	  *(SANE_Word*) value = word_list[1];
      break;

    case SANE_CONSTRAINT_STRING_LIST:


      string_list = opt->constraint.string_list;
      len = strlen (value);


      num_matches = 0;
      match = -1;
      for (i = 0; string_list[i]; ++i)
	if (strncasecmp (value, string_list[i], len) == 0
	    && len <= strlen (string_list[i]))
	  {
	    match = i;
	    if (len == strlen (string_list[i]))
	      {

		if (strcmp (value, string_list[i]) != 0)

		  strcpy (value, string_list[match]);
	      }
	    ++num_matches;
	  }

      if (num_matches > 1)


        strcpy(value, string_list[match]);
      else if (num_matches == 1)
        strcpy (value, string_list[match]);
      else
        strcpy (value, string_list[0]);

    default:
      break;
    }
}
