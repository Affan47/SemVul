type_find_factory_rank_cmp (const GstPluginFeature * fac1,
    const GstPluginFeature * fac2)
{
  if (G_LIKELY (fac1->rank != fac2->rank))
    return fac2->rank - fac1->rank;


  return strcmp (GST_OBJECT_NAME (fac1), GST_OBJECT_NAME (fac2));
}
