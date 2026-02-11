glade_base_editor_child_change_type (GladeBaseEditor *editor,
                                     GtkTreeIter *iter,
                                     GType type)
{
  GladeWidget *gchild;
  GObject *child;
  gchar *class_name;
  gboolean retval;

  glade_base_editor_block_callbacks (editor, TRUE);


  gtk_tree_model_get (editor->priv->model, iter,
                      GLADE_BASE_EDITOR_GWIDGET, &gchild,
                      GLADE_BASE_EDITOR_OBJECT, &child, -1);

  g_object_unref (gchild);
  g_object_unref (child);

  if (type == G_OBJECT_TYPE (child) ||
      !gchild || !glade_widget_get_parent (gchild))
    {
      glade_base_editor_block_callbacks (editor, FALSE);
      return;
    }


  if (glade_base_editor_get_type_info (editor, NULL,
                                       type,
                                       GLADE_BASE_EDITOR_CLASS_NAME,
                                       &class_name, -1))
    {
      glade_command_push_group (_("Setting object type on %s to %s"),
                                glade_widget_get_name (gchild), class_name);
      g_free (class_name);
    }
  else
    {
      glade_base_editor_block_callbacks (editor, FALSE);
      return;
    }

  g_signal_emit (editor,
                 glade_base_editor_signals[SIGNAL_CHANGE_TYPE],
                 0, gchild, type, &retval);


  glade_command_pop_group ();


  glade_base_editor_update_properties (editor);

  glade_base_editor_block_callbacks (editor, FALSE);
}
