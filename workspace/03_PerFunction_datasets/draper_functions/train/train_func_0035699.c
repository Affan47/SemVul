set_colour(colour c)
{
if (c.red   != setcolour.red ||
    c.green != setcolour.green ||
    c.blue  != setcolour.blue)
  {
  if (c.red == c.green && c.green == c.blue)
    {
    fprintf(out_file, ".graphgrey %s\n", fixed(c.red));
    }
  else
    {
    fprintf(out_file, ".graphcolour %s %s %s\n", fixed(c.red), fixed(c.green),
      fixed(c.blue));
    }
  setcolour = c;
  }
}
