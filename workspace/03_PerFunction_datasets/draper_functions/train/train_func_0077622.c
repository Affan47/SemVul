reset_pointers (FttCell * cell, GfsVariable ** v)
{
  guint i;
  for (i = 0; i < NV; i++)
    GFS_DOUBLE_TO_POINTER (GFS_VALUE (cell, v[i])) = NULL;
}
