fribidi_unicode_to_iso8859_8_c (

  FriBidiChar uch
)
{
  if (uch < 128)
    return (char) uch;
  if (uch >= UNI_ALEF && uch <= UNI_TAV)
    return (char) (uch - UNI_ALEF + ISO_ALEF);
  switch (uch)
    {
    case FRIBIDI_CHAR_RLM:
      return (char) ISO_8859_8_RLM;
    case FRIBIDI_CHAR_LRM:
      return (char) ISO_8859_8_LRM;
    case FRIBIDI_CHAR_RLO:
      return (char) ISO_8859_8_RLO;
    case FRIBIDI_CHAR_LRO:
      return (char) ISO_8859_8_LRO;
    case FRIBIDI_CHAR_RLE:
      return (char) ISO_8859_8_RLE;
    case FRIBIDI_CHAR_LRE:
      return (char) ISO_8859_8_LRE;
    case FRIBIDI_CHAR_PDF:
      return (char) ISO_8859_8_PDF;
    }
  return '?';
}
