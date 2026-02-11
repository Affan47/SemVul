_e_entry_cb_copy(void *data, E_Menu *m __UNUSED__, E_Menu_Item *mi __UNUSED__)
{
   E_Entry_Smart_Data *sd = data;
   const char *range;
   Ecore_X_Window xwin;
   E_Win *win;

   if (!sd) return;
   range = edje_object_part_text_selection_get(sd->entry_object, ENTRY_PART_NAME);
   if (range)
     {
        win = e_win_evas_object_win_get(sd->entry_object);
        if (win) xwin = win->evas_win;
        else
          {
             xwin = e_grabinput_key_win_get();
             if (!xwin)
               {
                  E_Container *con;

                  con = e_container_evas_object_container_get(sd->entry_object);
                  if (!con) return;
                  xwin = ecore_evas_window_get(con->bg_ecore_evas);
               }
          }
        ecore_x_selection_clipboard_set(xwin, range, strlen(range) + 1);
     }
}
