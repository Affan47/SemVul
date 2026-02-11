_keyPressed(GtkWidget* w, GdkEventKey* k, gpointer data)
    {
        if (k->keyval == GDK_Return)
            _replaceClicked(w, data);
    }
