_e_fm2_toomany_get(const E_Fm2_Smart_Data *sd)
{
   char mode;

   mode = sd->config->view.mode;
   if (sd->view_mode > -1) mode = sd->view_mode;
   if (((mode >= E_FM2_VIEW_MODE_CUSTOM_ICONS) &&
        (mode <= E_FM2_VIEW_MODE_CUSTOM_SMART_GRID_ICONS)) &&
       (eina_list_count(sd->icons) >= 500))
     return EINA_TRUE;
   return EINA_FALSE;
}
