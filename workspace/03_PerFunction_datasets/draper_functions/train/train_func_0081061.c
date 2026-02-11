surface(double x, double y, double z, double cutoff)
{
  int ncontact;
  double xs,ys,zs;
  double xnear[3],xorig[3];

  if (varshape && update->ntimestep != lastshape) {
    shape_update();
    lastshape = update->ntimestep;
  }

  if (dynamic) {
    xorig[0] = x;
    xorig[1] = y;
    xorig[2] = z;
    inverse_transform(x,y,z);
  }

  xnear[0] = x;
  xnear[1] = y;
  xnear[2] = z;

  if (interior) ncontact = surface_interior(xnear,cutoff);
  else ncontact = surface_exterior(xnear,cutoff);

  if (rotateflag && ncontact) {
    for (int i = 0; i < ncontact; i++) {
      xs = xnear[0] - contact[i].delx;
      ys = xnear[1] - contact[i].dely;
      zs = xnear[2] - contact[i].delz;
      forward_transform(xs,ys,zs);
      contact[i].delx = xorig[0] - xs;
      contact[i].dely = xorig[1] - ys;
      contact[i].delz = xorig[2] - zs;
    }
  }

  return ncontact;
}
