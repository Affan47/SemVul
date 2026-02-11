e_dialog_button_focus_num(E_Dialog *dia, int button)
{
   Evas_Object *o;

   o = eina_list_nth(dia->buttons, button);
   if (o) e_widget_focus_steal(o);
   return 1;
}
