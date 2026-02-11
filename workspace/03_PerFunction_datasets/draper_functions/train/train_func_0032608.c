frame_argument(Gt_Viewer *viewer, const char *arg)
{
  const char *c = arg;
  int n1 = 0;


  if (isdigit(c[0]))
    n1 = strtol(arg, (char **)&c, 10);


  if (c[0] != 0) {
    Gif_Image *gfi = Gif_GetNamedImage(viewer->gfs, c);
    if (!gfi)
      error("no frame named '%s'", c);
    else
      n1 = Gif_ImageNumber(viewer->gfs, gfi);
  } else {
    if (n1 < 0 || n1 >= viewer->nim) {
      error("no frame number %d", n1);
      n1 = 0;
    }
  }

  return n1;
}
