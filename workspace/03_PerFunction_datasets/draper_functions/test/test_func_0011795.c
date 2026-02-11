visu_plane_setDistanceFromOrigin(VisuPlane *plane, float dist)
{
  g_return_val_if_fail(VISU_IS_PLANE_TYPE(plane), FALSE);

  if (plane->dist == dist)
    return FALSE;

  plane->dist = dist;
  DBG_fprintf(stderr, "Visu VisuPlane : set distance from origin %f for plane %p.\n",
	      dist, (gpointer)plane);

  if (!plane->box)
    return TRUE;


  computeInter(plane);
  return TRUE;
}
