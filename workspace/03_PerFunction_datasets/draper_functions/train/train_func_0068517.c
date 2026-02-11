_e_qa_bd_menu_add(void *data, E_Menu *m __UNUSED__, E_Menu_Item *mi __UNUSED__)
{
   E_Border *bd = data;
   if (!bd) return;
   if (eg) return;
   eg = e_grab_dialog_show(NULL, EINA_FALSE, _grab_key_down_cb, NULL, NULL, bd);
   e_object_data_set(E_OBJECT(eg), bd);
   e_object_del_attach_func_set(E_OBJECT(eg), _grab_wnd_hide);
}
