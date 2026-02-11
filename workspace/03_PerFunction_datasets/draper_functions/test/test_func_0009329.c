run_tests (TestState *state)
{
  int i;

  for (i = 0; i < G_N_ELEMENTS (tests); i++)
    {
      cogl_framebuffer_clear4f (test_fb,
                                COGL_BUFFER_BIT_COLOR,
                                0, 0, 0, 1);

      tests[i] (state);
    }
}
