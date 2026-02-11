dGeomSetOffsetWorldPosition (dxGeom *g, dReal x, dReal y, dReal z)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  dUASSERT (g->body, "geom must be on a body");
  CHECK_NOT_LOCKED (g->parent_space);
  if (!g->offset_posr)
  {
	dGeomCreateOffset(g);
  }
  dBodyGetPosRelPoint(g->body, x, y, z, g->offset_posr->pos);
  dGeomMoved (g);
}
