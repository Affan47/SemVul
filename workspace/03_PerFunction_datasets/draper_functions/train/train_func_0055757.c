gegl_region_xor (GeglRegion       *source1,
                 const GeglRegion *source2)
{
  GeglRegion *trb;

  g_return_if_fail (source1 != NULL);
  g_return_if_fail (source2 != NULL);

  trb = gegl_region_copy (source2);

  gegl_region_subtract (trb, source1);
  gegl_region_subtract (source1, source2);

  gegl_region_union (source1, trb);

  gegl_region_destroy (trb);
}
