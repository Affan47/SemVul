gtk_form_move(GtkForm	*form,
	      GtkWidget	*child_widget,
	      gint	x,
	      gint	y)
{
    GList *tmp_list;
    GtkFormChild *child;

    g_return_if_fail(GTK_IS_FORM(form));

    for (tmp_list = form->children; tmp_list; tmp_list = tmp_list->next)
    {
	child = tmp_list->data;
	if (child->widget == child_widget)
	{
	    child->x = x;
	    child->y = y;

	    gtk_form_position_child(form, child, TRUE);
	    return;
	}
    }
}
