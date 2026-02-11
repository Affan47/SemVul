lf_attempt_axbxc(
  cct_cube cube,
  Display *display,
  Colormap colormap,
  int a,
  int b,
  int c)
{
  unsigned long allocated[256];
  int la, lb, lc;
  int n = 0;

  for(la = 0; la < a; la++)
  {
    cube->u.mapping.pixel_values[0][la] = b*c*la;
    for(lb = 0; lb < b; lb++)
    {
      cube->u.mapping.pixel_values[1][lb] = c*lb;
      for(lc = 0; lc < c; lc++)
      {
        XColor try;
        int status;
        cube->u.mapping.pixel_values[2][lc] = lc;
        try.red = (unsigned short)   (0.001+(65535.0 * la) / (double) (a - 1));
        try.green = (unsigned short) (0.001+(65535.0 * lb) / (double) (b - 1));
        try.blue = (unsigned short)  (0.001+(65535.0 * lc) / (double) (c - 1));
        cube->u.mapping.brightnesses[0][la] = try.red >> 8;
        cube->u.mapping.brightnesses[1][lb] = try.green >> 8;
        cube->u.mapping.brightnesses[2][lc] = try.blue >> 8;
        try.flags = DoRed | DoGreen | DoBlue;
        status = XAllocColor(display, colormap, &try);
        if(!status && n)
        {
          XFreeColors(display, colormap, allocated, n, 0);
          return(false);
        }
        cube->u.mapping.mapping[n] = try.pixel;
        allocated[n] = try.pixel;
        n++;
      }
    }
  }


  cube->cube_type = cube_mapping;
  cube->u.mapping.value_count[0] = a;
  cube->u.mapping.value_count[1] = b;
  cube->u.mapping.value_count[2] = c;

  if(getenv("CHIMERA_TEST_COLOR_ALLOCATION"))
    printf("%dx%dx%d color cube allocated\n", a, b, c);

  return true;
}
