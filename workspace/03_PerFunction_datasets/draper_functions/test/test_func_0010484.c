egg_keymap_get_modmap (GdkKeymap *keymap)
{
  EggModmap *modmap;


  modmap = g_object_get_data (G_OBJECT (keymap),
                              "egg-modmap");

  if (modmap == NULL)
    {
      modmap = g_new0 (EggModmap, 1);


      reload_modmap (keymap, modmap);

      g_object_set_data_full (G_OBJECT (keymap),
                              "egg-modmap",
                              modmap,
                              g_free);
    }

  g_assert (modmap != NULL);

  return modmap;
}
