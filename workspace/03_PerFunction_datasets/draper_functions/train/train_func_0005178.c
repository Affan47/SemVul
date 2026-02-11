egg_column_model_get_column_type (GtkTreeModel *tree_model,
				  gint          temp_index)
{
  switch (temp_index)
    {
    case COLUMN_VISIBLE:
      return G_TYPE_BOOLEAN;
    case COLUMN_NAME:
      return G_TYPE_STRING;
    case COLUMN_OBJECT:
      return GTK_TYPE_TREE_VIEW_COLUMN;
    default:
      return G_TYPE_INVALID;
    }
}
