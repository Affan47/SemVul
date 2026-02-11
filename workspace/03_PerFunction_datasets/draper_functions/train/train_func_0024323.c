read_geometry(GRect &r)
{
  int x,y,w,h,c;
  x = y = w = h = 0;
  if (read_integer(w) && expect(c, "x") && read_integer(h))
    {
      if (expect(c,"+-"))
        {
          if (c == '+')
            expect(c,"-");
          if (! read_integer(x))
            return false;
          if (c == '-')
            x = -x;
        }
      if (expect(c,"+-"))
        {
          if (c == '+')
            expect(c,"-");
          if (! read_integer(y))
            return false;
          if (c == '-')
            y = -y;
        }
      r = GRect(x,y,w,h);
      return true;
    }
  return false;
}
