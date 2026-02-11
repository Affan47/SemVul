inverse_cell (GfsMap * map, const FttVector * src, FttVector * dest)
{
  gint i;
  for (i = 0; i < 4; i++)
    (* map->inverse) (map, &(src[i]), &(dest[i]));
}
