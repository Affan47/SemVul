gegl_processor_is_rendered (GeglProcessor *processor)
{
  if (gegl_region_empty (processor->queued_region) &&
      processor->dirty_rectangles == NULL)
    return TRUE;
  return FALSE;
}
