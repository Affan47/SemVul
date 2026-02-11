gfs_source_electric_destroy (GtsObject * o)
{
  FttComponent c;
  for (c = 0; c < FTT_DIMENSION; c++)
    if (GFS_SOURCE_ELECTRIC (o)->fe[c])
      gts_object_destroy (GTS_OBJECT (GFS_SOURCE_ELECTRIC (o)->fe[c]));

  (* GTS_OBJECT_CLASS (gfs_source_electric_class ())->parent_class->destroy) (o) ;
}
