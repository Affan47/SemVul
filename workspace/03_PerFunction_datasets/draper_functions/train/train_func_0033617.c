cl_process (GeglOperation       *operation,
            GeglBuffer          *input,
            GeglBuffer          *output,
            const GeglRectangle *roi)
{
  const Babl *in_format  = gegl_operation_get_format (operation, "input");
  const Babl *out_format = gegl_operation_get_format (operation, "output");
  gint err;
  gint j;
  cl_int cl_err;

  GeglOperationAreaFilter *op_area = GEGL_OPERATION_AREA_FILTER (operation);
  GeglChantO *o = GEGL_CHANT_PROPERTIES (operation);

  GeglBufferClIterator *i = gegl_buffer_cl_iterator_new   (output,   roi, out_format, GEGL_CL_BUFFER_WRITE, GEGL_ABYSS_NONE);
                gint read = gegl_buffer_cl_iterator_add_2 (i, input, roi, in_format,  GEGL_CL_BUFFER_READ, op_area->left, op_area->right, op_area->top, op_area->bottom, GEGL_ABYSS_NONE);
                gint aux  = gegl_buffer_cl_iterator_add_2 (i, NULL,  roi, in_format,  GEGL_CL_BUFFER_AUX,  op_area->left, op_area->right, op_area->top, op_area->bottom, GEGL_ABYSS_NONE);
  while (gegl_buffer_cl_iterator_next (i, &err))
  {
    if (err) return FALSE;
    for (j=0; j < i->n; j++)
    {
      cl_err = cl_pixelise(i->tex[read][j], i->tex[aux][j], i->tex[0][j],&i->roi[read][j], &i->roi[0][j], o->size_x,o->size_y);
      if (cl_err != CL_SUCCESS)
      {
        g_warning("[OpenCL] Error in gegl:pixelise: %s", gegl_cl_errstring(cl_err));
        return FALSE;
      }
    }
  }
  return TRUE;
}
