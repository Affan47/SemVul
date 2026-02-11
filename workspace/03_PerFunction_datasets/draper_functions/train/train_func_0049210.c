tess_vertex_data(Vertex *vp, struct tess_data *data)
{
  if (data->plflags & PL_HASVCOL) D4F(&vp->vcol);
  if (data->plflags & PL_HASVN) N3F(&vp->vn, &vp->pt);
  if (data->plflags & PL_HASST) glTexCoord2fv((GLfloat *)&vp->st);
  glVertex4fv(&vp->pt.x);
}
