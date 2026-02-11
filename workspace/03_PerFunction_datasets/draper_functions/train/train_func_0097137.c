gtex_write_begin (FILE * f, unsigned char style)
{
  if (style == gregoriotex_ignore_style)
    {
      return;
    }
  switch (style)
    {
    case ST_ITALIC:
      fprintf (f, "\\greitalic{");
      break;
    case ST_SMALL_CAPS:
      fprintf (f, "\\gresmallcaps{");
      break;
    case ST_BOLD:
      fprintf (f, "\\greboldfont{");
      break;
    case ST_FORCED_CENTER:
    case ST_CENTER:
      fprintf (f, "}{");
      break;
    case ST_TT:
      fprintf (f, "\\grett{");
      break;
    case ST_UNDERLINED:
      fprintf (f, "\\greul{");
      break;
    default:
      break;
    }
}
