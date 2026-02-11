gfs_norm_update (GfsNorm * n)
{
  g_return_if_fail (n != NULL);

  if (n->w > 0.0) {
    n->bias /= n->w;
    n->first /= n->w;
    n->second = sqrt (n->second/n->w);
  }
  else
    n->infty = 0.0;
}
