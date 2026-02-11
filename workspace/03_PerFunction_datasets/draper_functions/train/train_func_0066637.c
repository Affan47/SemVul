gfs_boundary_lookup_bc (GfsBoundary * b, GfsVariable * v)
{
  GfsBc * bv;

  g_return_val_if_fail (b != NULL, NULL);
  g_return_val_if_fail (v != NULL, NULL);

  if (!v->name || !(bv = g_hash_table_lookup (b->bc, v->name))) {
    if (v->default_bc) {
      bv = v->default_bc;
      bv->b = b;
    }
    else
      bv = b->default_bc;
    bv->v = v;
  }
  return bv;
}
