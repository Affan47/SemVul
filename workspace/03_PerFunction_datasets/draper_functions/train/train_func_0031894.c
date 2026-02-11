gegl_affine_get_required_for_output (GeglOperation       *op,
                                     const gchar         *input_pad,
                                     const GeglRectangle *region)
{
  OpTransform      *affine = OP_AFFINE (op);
  GeglMatrix3    inverse;
  GeglRectangle  requested_rect,
                 need_rect;
  GeglRectangle  context_rect;
  GeglSampler   *sampler;
  gdouble        need_points [8];
  gint           i;

  requested_rect = *region;
  sampler = gegl_buffer_sampler_new (NULL, babl_format("RaGaBaA float"),
      gegl_sampler_type_from_string (affine->filter));
  context_rect = *gegl_sampler_get_context_rect (sampler);
  g_object_unref (sampler);

  gegl_affine_create_composite_matrix (affine, &inverse);
  gegl_matrix3_invert (&inverse);

  if (gegl_affine_is_intermediate_node (affine) ||
      gegl_matrix3_is_identity (&inverse))
    {
      return requested_rect;
    }

  need_points [0] = requested_rect.x;
  need_points [1] = requested_rect.y;

  need_points [2] = requested_rect.x + requested_rect.width ;
  need_points [3] = requested_rect.y;

  need_points [4] = requested_rect.x + requested_rect.width ;
  need_points [5] = requested_rect.y + requested_rect.height ;

  need_points [6] = requested_rect.x;
  need_points [7] = requested_rect.y + requested_rect.height ;

  for (i = 0; i < 8; i += 2)
    gegl_matrix3_transform_point (&inverse,
                             need_points + i, need_points + i + 1);
  gegl_affine_bounding_box (need_points, 4, &need_rect);

  need_rect.x      += context_rect.x;
  need_rect.y      += context_rect.y;
  need_rect.width  += context_rect.width;
  need_rect.height += context_rect.height;
  return need_rect;
}
