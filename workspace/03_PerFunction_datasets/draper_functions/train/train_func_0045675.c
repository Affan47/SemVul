face_setting_E_from_phi(FttCellFace *f, GfsBc * b)
{
  if (b->v->component == f->d/2) {
    GfsVariable * phi = GFS_ELECTRO_HYDRO (gfs_object_simulation(b))->phi;
    GfsGradient g;
    gfs_face_gradient (f, &g, phi->i, -1);
    double slope = (- g.b + g.a*GFS_VALUE (f->cell, phi))/ftt_cell_size (f->cell)
      *(FTT_FACE_DIRECT(f) ? 1 : -1);
    GFS_STATE (f->cell)->f[f->d].v =
      GFS_STATE (f->neighbor)->f[FTT_OPPOSITE_DIRECTION (f->d)].v = slope;
  }
  else
    GFS_STATE (f->cell)->f[f->d].v = GFS_VALUE (f->neighbor, b->v);
}
