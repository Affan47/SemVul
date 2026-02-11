colorCodeToName (int code)
{
  char *color_name[18]={
    "black",
    "dark red",
    "dark green",
    "dark yellow",
    "dark blue",
    "dark magenta",
    "dark cyan",
    "light gray",
    "dark gray",
    "red",
    "green",
    "yellow",
    "blue",
    "magenta",
    "cyan",
    "white",
    "transparent",
    "default"
  };
  if (code == 0x1f || code == 255)
    return color_name[17];
  if (code < 0 || code > 16)
    {
      if (debugging)
	printf("colorCodeToName: unexpected color code 0x%02X=%d, "
	       "assuming black\n", code, code);
      code = 0;
    }
  return color_name[code];
}
