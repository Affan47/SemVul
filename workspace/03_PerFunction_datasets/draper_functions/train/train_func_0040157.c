gegl_affine_get_bounding_box (GeglOperation *op)
{
  OpTransform      *affine  = OP_AFFINE (op);
  GeglMatrix3    matrix;
  GeglRectangle  in_rect = {0,0,0,0},
                 have_rect;
  gdouble        have_points [8];
  gint           i;

  GeglRectangle  context_rect;
  GeglSampler   *sampler;

  sampler = gegl_buffer_sampler_new (NULL, babl_format("RaGaBaA float"),
      gegl_sampler_type_from_string (affine->filter));
  context_rect = *gegl_sampler_get_context_rect (sampler);
  g_object_unref (sampler);

  if (gegl_operation_source_get_bounding_box (op, "input"))
    in_rect = *gegl_operation_source_get_bounding_box (op, "input");

  gegl_affine_create_composite_matrix (affine, &matrix);

  if (gegl_affine_is_intermediate_node (affine) ||
      gegl_matrix3_is_identity (&matrix))
    {
      return in_rect;
    }

  if (!gegl_affine_matrix3_allow_fast_translate (&matrix))
    {
      in_rect.x      += context_rect.x;
      in_rect.y      += context_rect.y;
      in_rect.width  += context_rect.width;
      in_rect.height += context_rect.height;
    }

  have_points [0] = in_rect.x;
  have_points [1] = in_rect.y;

  have_points [2] = in_rect.x + in_rect.width ;
  have_points [3] = in_rect.y;

  have_points [4] = in_rect.x + in_rect.width ;
  have_points [5] = in_rect.y + in_rect.height ;

  have_points [6] = in_rect.x;
  have_points [7] = in_rect.y + in_rect.height ;

  for (i = 0; i < 8; i += 2)
    gegl_matrix3_transform_point (&matrix,
                             have_points + i, have_points + i + 1);

  gegl_affine_bounding_box (have_points, 4, &have_rect);
  return have_rect;
}
