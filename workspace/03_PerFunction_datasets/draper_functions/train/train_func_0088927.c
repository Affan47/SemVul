_e_xkb_cb_lmenu_post(void *data, E_Menu *menu __UNUSED__)
{
   Instance *inst = data;

   if (!inst) return;
   e_gadcon_locked_set(inst->gcc->gadcon, 0);
   inst->lmenu = NULL;
}
