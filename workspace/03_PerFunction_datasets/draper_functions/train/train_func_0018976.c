glade_base_editor_add_child (GladeBaseEditor       *editor,
                             GType                  type,
			     GladeBaseEditorAddMode add_mode)
{
  GladeBaseEditorPrivate *e = editor->priv;
  GtkTreeIter iter, new_iter;
  GladeWidget *gparent, *gchild_new;
  gchar *name, *class_name;
  gboolean selected_iter = FALSE;

  glade_base_editor_block_callbacks (editor, TRUE);

  gparent = e->gcontainer;

  if (add_mode != ADD_ROOT &&
      (selected_iter = glade_base_editor_get_child_selected (editor, &iter)))
    {
      if (add_mode == ADD_CHILD)
	{
	  gtk_tree_model_get (e->model, &iter,
			      GLADE_BASE_EDITOR_GWIDGET, &gparent, -1);
	  g_object_unref (gparent);
	}
      else if (add_mode == ADD_SIBLING &&
	       gtk_tree_model_iter_parent (e->model, &new_iter, &iter))
        {
          gtk_tree_model_get (e->model, &new_iter,
                              GLADE_BASE_EDITOR_GWIDGET, &gparent, -1);
	  g_object_unref (gparent);
        }
    }

  if (!glade_base_editor_get_type_info (editor, NULL, type,
                                        GLADE_BASE_EDITOR_CLASS_NAME,
                                        &class_name, -1))
    return;

  glade_command_push_group (_("Add a %s to %s"), class_name,
                            glade_widget_get_name (gparent));


  gchild_new = glade_base_editor_delegate_build_child (editor, gparent, type);

  if (gchild_new == NULL)
    {
      glade_command_pop_group ();
      return;
    }

  if (selected_iter)
    {
      if (add_mode == ADD_CHILD)
        gtk_tree_store_append (GTK_TREE_STORE (editor->priv->model), &new_iter,
                               &iter);
      else
        gtk_tree_store_insert_after (GTK_TREE_STORE (editor->priv->model),
                                     &new_iter, NULL, &iter);
    }
  else
    gtk_tree_store_append (GTK_TREE_STORE (editor->priv->model), &new_iter,
                           NULL);

  name = glade_base_editor_get_display_name (editor, gchild_new);

  gtk_tree_store_set (GTK_TREE_STORE (editor->priv->model), &new_iter,
                      GLADE_BASE_EDITOR_GWIDGET, gchild_new,
                      GLADE_BASE_EDITOR_OBJECT,
                      glade_widget_get_object (gchild_new),
                      GLADE_BASE_EDITOR_TYPE_NAME, class_name,
                      GLADE_BASE_EDITOR_NAME, name,
                      GLADE_BASE_EDITOR_CHILD_TYPES,
                      get_children_model_for_type (editor,
                                                   G_OBJECT_TYPE (glade_widget_get_object (gparent))),
		      -1);

  glade_base_editor_reorder_children (editor, &new_iter);

  gtk_tree_view_expand_all (GTK_TREE_VIEW (e->treeview));
  glade_base_editor_set_cursor (editor, &new_iter);

  glade_command_pop_group ();

  glade_base_editor_block_callbacks (editor, FALSE);

  g_free (name);
  g_free (class_name);
}
