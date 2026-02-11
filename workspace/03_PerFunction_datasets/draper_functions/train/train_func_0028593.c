_cb_menu_sel(void *data, E_Menu *m, E_Menu_Item *mi __UNUSED__)
{
   E_Config_Syscon_Action *sca;
   E_Action *act;

   e_menu_deactivate(m);
   if (!(sca = data)) return;
   if (!(act = e_action_find(sca->action))) return;
   act->func.go(NULL, sca->params);
}
