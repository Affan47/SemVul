face_too_coarse (FttCellFace * face, VofParms * p)
{
  if (ftt_face_type (face) == FTT_FINE_COARSE) {
    gdouble un = GFS_FACE_NORMAL_VELOCITY (face);
    if (!FTT_FACE_DIRECT (face))
      un = - un;
    if (un > 0.) {
      gdouble f = GFS_VALUE (face->neighbor, p->par->v);
      if (GFS_IS_FULL (f) &&
	  fine_fraction (face, p, un*p->par->dt/ftt_cell_size (face->cell)) != f) {
	p->too_coarse++;
	TOO_COARSE (face->neighbor) = TRUE;
      }
    }
  }
}
