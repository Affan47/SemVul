glade_base_editor_move_child (GladeBaseEditor * editor,
                              GladeWidget * gparent, GladeWidget * gchild)
{
  GList list = { 0, };

  if (gparent != glade_widget_get_parent (gchild))
    {
      list.data = gchild;
      glade_command_dnd (&list, gparent, NULL);
    }

  return TRUE;
}
