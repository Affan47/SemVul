dump_element_type (char element_type)
{
  const char *str;
  switch (element_type)
    {
    case 0:
      str = "ELT_NO_ELEMENT";
      break;
    case 1:
      str = "ELT_PRAEPUNCTA";
      break;
    case 2:
      str = "ELT_ONE_GLYPH";
      break;
    case 3:
      str = "ELT_PRAEPUNCTA_ONE_GLYPH";
      break;
    case 4:
      str = "ELT_TWO_GLYPH";
      break;
    case 5:
      str = "ELT_PRAEPUNCTA_TWO_GLYPH";
      break;
    case 6:
      str = "ELT_ONE_GLYPH_SUBPUNCTA";
      break;
    case 7:
      str = "ELT_PRAEPUNCTA_ONE_GLYPH_SUBPUNCTA";
      break;
    case 8:
      str = "ELT_TWO_GLYPH_SUBPUNCTA";
      break;
    case 9:
      str = "ELT_PRAEPUNCTA_TWO_GLYPH_SUBPUNCTA";
      break;
    default:
      str = "unknown";
      break;
    }
  return str;
}
