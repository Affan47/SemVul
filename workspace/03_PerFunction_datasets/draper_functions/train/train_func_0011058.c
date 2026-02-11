info_panel_setup_default_apps (CcInfoPanel  *self)
{
  int i;

  for (i = 0; i < G_N_ELEMENTS(preferred_app_infos); i++)
    {
      info_panel_setup_default_app (self, &preferred_app_infos[i],
                                    1, 2, i, i+1);
    }
}
