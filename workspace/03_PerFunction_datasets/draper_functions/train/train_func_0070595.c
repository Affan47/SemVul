otex_write_begin (FILE * f, unsigned char style)
{
  switch (style)
    {
    case ST_ITALIC:
      fprintf (f, "{\\it ");
      break;
    case ST_SMALL_CAPS:
      fprintf (f, "{\\sc ");
      break;
    case ST_BOLD:
      fprintf (f, "{\\bf ");
      break;
    case ST_FORCED_CENTER:
    case ST_CENTER:
      fprintf (f, "}{");
      break;
    case ST_TT:
      fprintf (f, "{\\tt ");
      break;
    default:
      break;
    }
}
