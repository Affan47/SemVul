_e_imc_change_enqueue(E_Config_Dialog_Data *cfdata)
{
   if (cfdata->imc.dirty)
     {
        E_Input_Method_Config *imc_update;
        E_Input_Method_Config *imc_update_old;

        imc_update = E_NEW(E_Input_Method_Config, 1);

        imc_update->version = E_INTL_INPUT_METHOD_CONFIG_VERSION;


        imc_update->e_im_name = eina_stringshare_add(cfdata->imc.e_im_name);
        imc_update->e_im_exec = eina_stringshare_add(cfdata->imc.e_im_exec);
        imc_update->e_im_setup_exec = eina_stringshare_add(cfdata->imc.e_im_setup_exec);
        imc_update->gtk_im_module = eina_stringshare_add(cfdata->imc.gtk_im_module);
        imc_update->qt_im_module = eina_stringshare_add(cfdata->imc.qt_im_module);
        imc_update->xmodifiers = eina_stringshare_add(cfdata->imc.xmodifiers);


        imc_update_old = eina_hash_find(cfdata->imc_change_map, cfdata->imc_current);
        if (imc_update_old)
          {
             eina_hash_del(cfdata->imc_change_map, cfdata->imc_current, NULL);
             e_intl_input_method_config_free(imc_update_old);
          }
        if (!cfdata->imc_change_map)
          cfdata->imc_change_map = eina_hash_string_superfast_new(NULL);
        eina_hash_add(cfdata->imc_change_map, cfdata->imc_current, imc_update);
     }
}
