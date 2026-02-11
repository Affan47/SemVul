gfs_generic_surface_read (GfsGenericSurface * s, gpointer sim, GtsFile * fp)
{
  GtsObject * o = (GtsObject *) s;

  g_return_if_fail (s != NULL);
  g_return_if_fail (fp != NULL);

  o->reserved = sim;
  (* GTS_OBJECT (s)->klass->read) (&o, fp);
}
