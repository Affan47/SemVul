do_test (const char *attribute_name,
         void (* pipeline_setup_func) (CoglPipeline *pipeline))
{
  int fb_width = cogl_framebuffer_get_width (test_fb);
  int fb_height = cogl_framebuffer_get_height (test_fb);
  CoglPrimitive *primitive;
  CoglPipeline *pipeline;
  int i;

  cogl_framebuffer_orthographic (test_fb,
                                 0, 0,
                                 fb_width,
                                 fb_height ,
                                 -1, 100 );

  cogl_framebuffer_clear4f (test_fb,
                            COGL_BUFFER_BIT_COLOR,
                            1.0f, 0.0f, 0.0f, 1.0f);

  primitive = create_primitive (attribute_name);
  pipeline = cogl_pipeline_new (test_ctx);
  cogl_pipeline_set_color4ub (pipeline, 0x00, 0xff, 0x00, 0xff);
  cogl_pipeline_set_per_vertex_point_size (pipeline, TRUE, NULL);
  if (pipeline_setup_func)
    pipeline_setup_func (pipeline);
  cogl_primitive_draw (primitive, test_fb, pipeline);
  cogl_object_unref (pipeline);
  cogl_object_unref (primitive);


  for (i = 0; i < N_POINTS; i++)
    verify_point_size (test_fb,
                       i * POINT_BOX_SIZE + POINT_BOX_SIZE / 2,
                       POINT_BOX_SIZE / 2,
                       MAX_POINT_SIZE - i );

  if (cogl_test_verbose ())
    g_print ("OK\n");
}
