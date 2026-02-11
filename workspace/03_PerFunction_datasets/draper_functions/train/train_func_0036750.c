init()
{


  avec_ellipsoid = (AtomVecEllipsoid *) atom->style_match("ellipsoid");
  avec_line = (AtomVecLine *) atom->style_match("line");
  avec_tri = (AtomVecTri *) atom->style_match("tri");
  if (!avec_ellipsoid && !avec_line && !avec_tri)
    error->all(FLERR,"Compute erotate/asphere requires "
               "atom style ellipsoid or line or tri");


  int *ellipsoid = atom->ellipsoid;
  int *line = atom->line;
  int *tri = atom->tri;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

  int flag;
  for (int i = 0; i < nlocal; i++)
    if (mask[i] & groupbit) {
      flag = 0;
      if (ellipsoid && ellipsoid[i] >= 0) flag = 1;
      if (line && line[i] >= 0) flag = 1;
      if (tri && tri[i] >= 0) flag = 1;
      if (!flag)
        error->one(FLERR,"Compute erotate/asphere requires extended particles");
    }

  pfactor = 0.5 * force->mvv2e;
}
