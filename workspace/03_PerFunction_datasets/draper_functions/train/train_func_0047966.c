gdl_dock_paned_request_foreach (GdlDockObject *object,
                                gpointer       user_data)
{
    struct {
        GtkWidget *parent;
        gint            x, y;
        GdlDockRequest *request;
        gboolean        may_dock;
    } *data = user_data;

    gint child_x, child_y;
    GdlDockRequest my_request;
    gboolean       may_dock;


    gtk_widget_translate_coordinates (data->parent, GTK_WIDGET (object), data->x, data->y, &child_x, &child_y);

    my_request = *data->request;
    may_dock = gdl_dock_object_dock_request (object, child_x, child_y, &my_request);
    if (may_dock) {

        gtk_widget_translate_coordinates (GTK_WIDGET (object), data->parent, my_request.rect.x, my_request.rect.y, &my_request.rect.x, &my_request.rect.y);
        data->may_dock = TRUE;
        *data->request = my_request;
    }
}
