BBoxFSave(BBox *bbox, FILE *f, char *fname)
{
  int i;

  if (bbox->pdim == 4) {
    fprintf(f, "BBOX\n");
  } else {
    fprintf(f, "nBBOX %d\n", bbox->pdim-1);
  }
  for (i = 1; i < bbox->pdim; i++) {
    fprintf(f, " %g", bbox->min->v[i]);
  }
  fprintf(f, "\n");
  for (i = 1; i < bbox->pdim; i++) {
    fprintf(f, " %g", bbox->max->v[i]);
  }
  return bbox;
}
