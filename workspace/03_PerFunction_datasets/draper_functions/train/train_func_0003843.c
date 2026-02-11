_e_config_dialog_check_changed(E_Config_Dialog *cfd, unsigned char def)
{
   int changed = 0;

   if (cfd->view_type == E_CONFIG_DIALOG_CFDATA_TYPE_BASIC)
     {
        if (cfd->view->basic.check_changed)
          changed = cfd->view->basic.check_changed(cfd, cfd->cfdata);
        else
          changed = def;
     }
   else if (cfd->view_type == E_CONFIG_DIALOG_CFDATA_TYPE_ADVANCED)
     {
        if (cfd->view->advanced.check_changed)
          changed = cfd->view->advanced.check_changed(cfd, cfd->cfdata);
        else
          changed = def;
     }

   return changed;
}
