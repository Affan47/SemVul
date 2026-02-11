test_color_mask (void)
{
  TestState state;
  int i;

  state.width = cogl_framebuffer_get_width (test_fb);
  state.height = cogl_framebuffer_get_height (test_fb);

  for (i = 0; i < NUM_FBOS; i++)
    {
      state.tex[i] = test_utils_texture_new_with_size (test_ctx, 128, 128,
                                                 TEST_UTILS_TEXTURE_NO_ATLAS,
                                                 COGL_PIXEL_FORMAT_RGB_888);


      state.fbo[i] = COGL_FRAMEBUFFER (
        cogl_offscreen_new_with_texture (state.tex[i]));


      cogl_framebuffer_clear4f (state.fbo[i],
                                COGL_BUFFER_BIT_COLOR, 0, 0, 0, 1);

      cogl_framebuffer_set_color_mask (state.fbo[i],
                                       i == 0 ? COGL_COLOR_MASK_RED :
                                       i == 1 ? COGL_COLOR_MASK_GREEN :
                                       COGL_COLOR_MASK_BLUE);
    }


  cogl_push_framebuffer (test_fb);
  paint (&state);
  cogl_pop_framebuffer ();

  if (cogl_test_verbose ())
    g_print ("OK\n");
}
