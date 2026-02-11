_12_try_restore_configuration(void)
{
   E_Randr_Serialized_Setup_12 *ss_12;
   E_Randr_Serialized_Crtc *sc;
   E_Randr_Crtc_Info *ci;
   Ecore_X_Randr_Output *outputs_array;
   E_Randr_Output_Info *output_info;
   Ecore_X_Randr_Mode_Info *mi = NULL;
   Ecore_X_Randr_Mode mode = 0;
   Eina_List *iter, *outputs_list, *outputs_iter;
   Eina_Bool ret = EINA_TRUE;

   EINA_SAFETY_ON_NULL_RETURN_VAL(e_config, EINA_FALSE);
   EINA_SAFETY_ON_NULL_RETURN_VAL(e_config->randr_serialized_setup, EINA_FALSE);

   if (!(ss_12 = _matching_serialized_setup_get(e_config->randr_serialized_setup->serialized_setups_12)))
     return EINA_FALSE;

   INF("E_RANDR: Found matching serialized setup.");
   EINA_LIST_FOREACH(ss_12->crtcs, iter, sc)
     {
        ci = _find_matching_crtc(sc);
        if (!ci)
          {
             ERR("E_RANDR: Cannot find a matching CRTC for serialized CRTC index %d.", sc->index);
             return EINA_FALSE;
          }
        outputs_list = _find_matching_outputs(sc->outputs);
        outputs_array = _outputs_to_array(outputs_list);

        if (!sc->mode_info)
          {
             INF("E_RANDR: \tSerialized mode was disabled.");
             mode = Ecore_X_Randr_None;
          }
        else if ((mi = _find_matching_mode_info(sc->mode_info)))
          {
             INF("E_RANDR: \tSerialized mode is now known under the name %s.", mi->name);
             mode = mi->xid;
          }
        else if (mi)
          {

             mi->name = malloc(MODE_STR_LENGTH_MAX);

             snprintf(mi->name, (MODE_STR_LENGTH_MAX - 1), "%ux%u,%lu,%lu", sc->mode_info->width, sc->mode_info->height, sc->mode_info->dotClock, sc->mode_info->modeFlags);
             mi = sc->mode_info;
             mode = ecore_x_randr_mode_info_add(e_randr_screen_info.root, mi);
             if (mode == Ecore_X_Randr_None)
               {
                  eina_list_free(outputs_list);
                  free(outputs_array);
                  continue;
               }
             EINA_LIST_FOREACH(outputs_list, outputs_iter, output_info)
                ecore_x_randr_output_mode_add(output_info->xid, mode);
             INF("E_RANDR: \tSerialized mode was added to the server manually using the name %s.", mi->name);
          }


        if (mi)
          DBG("E_RANDR: \tRestoring CRTC %d (index %d) in mode %s.", ci->xid, sc->index, (mode == Ecore_X_Randr_None) ? "(disabled)" : mi->name);
        DBG("E_RANDR: \t\tUsed outputs:");
        EINA_LIST_FOREACH(outputs_list, outputs_iter, output_info)
            DBG("\t\t%s", output_info->name);


        ret &= ecore_x_randr_crtc_settings_set(e_randr_screen_info.root, ci->xid, outputs_array, eina_list_count(outputs_list), sc->pos.x, sc->pos.y, mode, sc->orientation);
        eina_list_free(outputs_list);
        free(outputs_array);
     }
   return ret;
}
