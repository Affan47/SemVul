hoz_getsize()
{
    gchar baz[101];
    const gchar *foo, *qux;
    size_t bar, mult;

    foo =
        gtk_entry_get_text(GTK_ENTRY
                           (lookup_widget
                            (GTK_WIDGET(window_hoz), "entry_size")));
    qux = gtk_entry_get_text(GTK_ENTRY(lookup_widget(GTK_WIDGET(window_hoz),\
		    "combo_entry_size")));
    if (!strcmp(qux, "MiB")) {
	mult = 1024*1024;
    } else if (!strcmp(qux, "KiB")) {
	mult = 1024;
    } else {
	mult = 1;
    }
    bar = (size_t) atolmp((char *) foo, mult);
    partsize = (bar) ? bar : 0;
    if (!partsize && strlen(foo)) {
        sprintf(baz, HOZ_BADSIZE, foo);
        if (!window_bs) {
            window_bs = create_dialog_bs();
        }
        gtk_window_set_title(GTK_WINDOW(window_bs), HOZ_PROGRAM);
        gtk_label_set_label(GTK_LABEL
                            (lookup_widget
                             (GTK_WIDGET(window_bs), "label_msg_bs")),
                            baz);
        gtk_button_set_label(GTK_BUTTON
                             (lookup_widget
                              (GTK_WIDGET(window_bs), "okbutton_bs")),
                             "Ok");
        gtk_widget_show(window_bs);
    }
    return partsize;
}
