goo_canvas_accessible_ref_child (AtkObject *object,
				 gint       child_num)
{
  GtkAccessible *accessible;
  GtkWidget *widget;
  GooCanvasItem *root;
  AtkObject *atk_object;


  if (child_num != 0)
    return NULL;

  accessible = GTK_ACCESSIBLE (object);
  widget = gtk_accessible_get_widget (accessible);


  if (widget == NULL)
    return NULL;

  root = goo_canvas_get_root_item (GOO_CANVAS (widget));
  if (!root)
    return NULL;

  atk_object = atk_gobject_accessible_for_object (G_OBJECT (root));
  g_object_ref (atk_object);

  return atk_object;
}
