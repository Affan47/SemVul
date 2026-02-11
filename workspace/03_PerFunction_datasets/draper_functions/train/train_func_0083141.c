e_desktop_border_edit(E_Container *con, E_Border *bd)
{
   E_Desktop_Edit *editor;
   int new_desktop = 0;

   if (!con) return NULL;
   editor = E_OBJECT_ALLOC(E_Desktop_Edit, E_DESKTOP_EDIT_TYPE, _e_desktop_edit_free);
   if (!editor) return NULL;
   if (bd->desktop)
     editor->desktop = bd->desktop;


   if (!editor->desktop)
     {
        editor->desktop = e_desktop_border_create(bd);
        if ((editor->desktop) && (editor->desktop->icon))
          editor->tmp_image_path = strdup(editor->desktop->icon);
        new_desktop = 1;
     }

#if 0
   if ((!bname) && (!bclass))
     {
        e_util_dialog_show(_("Incomplete Window Properties"),
                           _("The window you are creating an icon for<br>"
                             "does not contain window name and class<br>"
                             "properties. Without these, you will have to<br>"
                             "use the window title instead. This will only<br>"
                             "work if the window title is the same at<br>"
                             "the time the window starts up, and does not<br>"
                             "change."));
     }
#endif
   if (!_e_desktop_edit_view_create(editor, con))
     {
        e_object_del(E_OBJECT(editor));
        editor = NULL;
     }
   else
     e_config_dialog_changed_set(editor->cfd, new_desktop);

   return editor;
}
