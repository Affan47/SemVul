quit_sdl(void)
{
  FC_FREE(Main.guis);
  gui_layer_destroy(&Main.gui);
  FREESURFACE(Main.map);
  FREESURFACE(Main.dummy);
}
