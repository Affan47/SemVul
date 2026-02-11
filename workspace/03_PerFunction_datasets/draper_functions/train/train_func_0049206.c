os_string_width (const zchar *s)
{
    int width = 0;
    zchar c;

    while ((c = *s++) != 0)

      if (c == ZC_NEW_STYLE || c == ZC_NEW_FONT) {

	s++;


      } else width += os_char_width(c);

    return width;

}
