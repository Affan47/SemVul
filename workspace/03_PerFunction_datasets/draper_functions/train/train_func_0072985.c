gln_graphics_open (void)
{
  if (!gln_graphics_window)
    {
      gln_graphics_window = glk_window_open (gln_main_window,
                                             winmethod_Above
                                             | winmethod_Proportional,
                                             GLN_GRAPHICS_PROPORTION,
                                             wintype_Graphics, 0);
    }

  return gln_graphics_window != NULL;
}
