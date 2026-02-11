nemo_path_bar_forall (GtkContainer *container,
		     	  gboolean      include_internals,
		     	  GtkCallback   callback,
		     	  gpointer      callback_data)
{
        NemoPathBar *path_bar;
        GList *children;

        g_return_if_fail (callback != NULL);
        path_bar = NEMO_PATH_BAR (container);

        children = path_bar->button_list;
        while (children) {
               GtkWidget *child;
               child = BUTTON_DATA (children->data)->button;
                children = children->next;
                (* callback) (child, callback_data);
        }

        if (path_bar->up_slider_button) {
                (* callback) (path_bar->up_slider_button, callback_data);
	}

        if (path_bar->down_slider_button) {
                (* callback) (path_bar->down_slider_button, callback_data);
	}
}
