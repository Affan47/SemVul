process (GeglOperation       *operation,
         GeglBuffer          *input,
         GeglBuffer          *output,
         const GeglRectangle *roi,
         gint                 level)
{
  GeglRectangle src_rect;
  GeglChantO *o = GEGL_CHANT_PROPERTIES (operation);
  GeglOperationAreaFilter *op_area;
  gfloat* buf;

  op_area = GEGL_OPERATION_AREA_FILTER (operation);
  src_rect = *roi;
  src_rect.x -= op_area->left;
  src_rect.y -= op_area->top;
  src_rect.width += op_area->left + op_area->right;
  src_rect.height += op_area->top + op_area->bottom;

  if (gegl_cl_is_accelerated ())
    if (cl_process (operation, input, output, roi))
      return TRUE;

  buf = g_new0 (gfloat, src_rect.width * src_rect.height * 4);

  gegl_buffer_get (input, &src_rect, 1.0, babl_format ("RaGaBaA float"), buf, GEGL_AUTO_ROWSTRIDE, GEGL_ABYSS_NONE);

  pixelize(buf, roi, o->size_x, o->size_y);

  gegl_buffer_set (output, roi, 0, babl_format ("RaGaBaA float"), buf, GEGL_AUTO_ROWSTRIDE);

  g_free (buf);

  return  TRUE;
}
