test_push_pop_multi_context (void)
{
  CoglTexture *offscreen_texture0;
  CoglOffscreen *offscreen0;
  CoglPipeline *pipeline0;
  CoglGLES2Context *gles2_ctx0;
  const CoglGLES2Vtable *gles20;
  CoglTexture *offscreen_texture1;
  CoglOffscreen *offscreen1;
  CoglPipeline *pipeline1;
  CoglGLES2Context *gles2_ctx1;
  const CoglGLES2Vtable *gles21;
  CoglError *error = NULL;

  create_gles2_context (&offscreen_texture0,
                        &offscreen0,
                        &pipeline0,
                        &gles2_ctx0,
                        &gles20);

  create_gles2_context (&offscreen_texture1,
                        &offscreen1,
                        &pipeline1,
                        &gles2_ctx1,
                        &gles21);

  cogl_framebuffer_clear4f (test_fb, COGL_BUFFER_BIT_COLOR, 1, 1, 1, 1);

  if (!cogl_push_gles2_context (test_ctx,
                                gles2_ctx0,
                                COGL_FRAMEBUFFER (offscreen0),
                                COGL_FRAMEBUFFER (offscreen0),
                                &error))
    {
      g_error ("Failed to push gles2 context 0: %s\n", error->message);
    }

  gles20->glClearColor (1, 0, 0, 1);
  gles20->glClear (GL_COLOR_BUFFER_BIT);

  if (!cogl_push_gles2_context (test_ctx,
                                gles2_ctx1,
                                COGL_FRAMEBUFFER (offscreen1),
                                COGL_FRAMEBUFFER (offscreen1),
                                &error))
    {
      g_error ("Failed to push gles2 context 1: %s\n", error->message);
    }

  gles21->glClearColor (0, 1, 0, 1);
  gles21->glClear (GL_COLOR_BUFFER_BIT);

  cogl_pop_gles2_context (test_ctx);
  cogl_pop_gles2_context (test_ctx);

  test_utils_check_pixel (test_fb, 0, 0, 0xffffffff);

  cogl_framebuffer_draw_rectangle (test_fb,
                                   pipeline0,
                                   -1, 1, 1, -1);

  test_utils_check_pixel (test_fb, 0, 0, 0xff0000ff);

  cogl_framebuffer_draw_rectangle (test_fb,
                                   pipeline1,
                                   -1, 1, 1, -1);

  test_utils_check_pixel (test_fb, 0, 0, 0x00ff00ff);
}
