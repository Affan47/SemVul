ChangeFontTo(FILE *out, char *color, weight_type weight)
{
  switch(weight)
    {
    case NO_CHANGE:
      break;
    case BOLD:
      if (BOLD != config.currentWeight)
	{
	  if (NULL != config.currentColor)
	    {
	      MyStringOutput(out, "</font>");
	      config.currentColor = NULL;
	    }
	  MyStringOutput(out, "<strong>");
	  config.currentWeight = BOLD;
	}
      break;
    case NORMAL:
      if (NORMAL != config.currentWeight)
	{
	  if (NULL != config.currentColor)
	    {
	      MyStringOutput(out, "</font>");
	      config.currentColor = NULL;
	    }
	  MyStringOutput(out, "</strong>");
	  config.currentWeight = NORMAL;
	}
      break;
    default:
      fprintf (stderr, "internal error: bad weight\n");
    }

  if (color != config.currentColor)
    {
      if (NULL != config.currentColor)
	{
	  MyStringOutput(out, "</font>");
	  config.currentColor = NULL;
	}
      if (NULL != color)
	{
	  MyStringOutput(out, "<font color=");
	  MyStringOutput(out, color);
	  MyStringOutput(out, ">");
	  config.currentColor = color;
	}
    }

  if (color != config.currentColor)
    { fprintf(stderr, "internal error in ChangeFontTo\n"); }
}
