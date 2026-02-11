pp_c_char (ppi, c)
     c_pretty_printer ppi;
     int c;
{
  switch (c)
    {
    case TARGET_NEWLINE:
      pp_identifier (ppi, "\\n");
      break;
    case TARGET_TAB:
      pp_identifier (ppi, "\\t");
      break;
    case TARGET_VT:
      pp_identifier (ppi, "\\v");
      break;
    case TARGET_BS:
      pp_identifier (ppi, "\\b");
      break;
    case TARGET_CR:
      pp_identifier (ppi, "\\r");
      break;
    case TARGET_FF:
      pp_identifier (ppi, "\\f");
      break;
    case TARGET_BELL:
      pp_identifier (ppi, "\\a");
      break;
    case '\\':
      pp_identifier (ppi, "\\\\");
      break;
    case '\'':
      pp_identifier (ppi, "\\'");
      break;
    case '\"':
      pp_identifier (ppi, "\\\"");
      break;
    default:
      if (ISPRINT (c))
	pp_character (ppi, c);
      else
	pp_format_scalar (ppi, "\\%03o", (unsigned) c);
      break;
    }
}
