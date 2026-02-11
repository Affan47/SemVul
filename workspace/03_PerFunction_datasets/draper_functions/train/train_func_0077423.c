string_value_combo_set_active(GtkWidget *widget,
                                          int value)
{
   GtkTreeIter iter;
   GtkTreeModel *model;
   int val;

   model = gtk_combo_box_get_model(GTK_COMBO_BOX(widget));
   gtk_tree_model_get_iter_first(model, &iter);
   do
   {
      gtk_tree_model_get(model, &iter, COMBO_VALUE, &val, -1);
      if(val == value)
      {
         gtk_combo_box_set_active_iter(GTK_COMBO_BOX(widget), &iter);
         break;
      }
   } while(gtk_tree_model_iter_next(model, &iter));
}
