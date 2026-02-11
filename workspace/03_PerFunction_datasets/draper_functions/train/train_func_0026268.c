e_int_border_prop(E_Border *bd)
{
   E_Dialog *dia;

   if (bd->border_prop_dialog) return;

   dia = e_dialog_new(bd->zone->container, "E", "_window_props");
   e_object_del_attach_func_set(E_OBJECT(dia), _bd_cb_dialog_del);

   _create_data(dia, bd);

   _bd_go(dia, (void *)0);

   e_dialog_button_add(dia, _("Close"), NULL, _bd_cb_dialog_close, dia);
   e_win_centered_set(dia->win, 1);
   e_dialog_show(dia);
   e_dialog_border_icon_set(dia, "preferences-system-windows");
}
