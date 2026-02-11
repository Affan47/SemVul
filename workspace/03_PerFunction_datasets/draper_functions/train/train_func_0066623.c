test_depth_test (void)
{
  TestState state;

  cogl_framebuffer_orthographic (test_fb, 0, 0,
                                 cogl_framebuffer_get_width (test_fb),
                                 cogl_framebuffer_get_height (test_fb),
                                 -1,
                                 100);

  paint (&state);

  if (cogl_test_verbose ())
    g_print ("OK\n");
}
