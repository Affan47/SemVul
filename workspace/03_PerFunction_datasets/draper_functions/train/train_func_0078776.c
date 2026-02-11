menubar_create (GtkWidget *window)
{
    GtkWidget      *menubar;
    GtkActionGroup *actgrp;
    GtkUIManager   *uimgr;
    GtkAccelGroup  *accgrp;
    GError         *error = NULL;


    gint           i;


    actgrp = gtk_action_group_new ("MenuActions");

       for (i=0; i<G_N_ELEMENTS (entries); i++) {
        if (entries[i].label)
            entries[i].label = _(entries[i].label);
        if (entries[i].tooltip)
            entries[i].tooltip = _(entries[i].tooltip);
    }

    gtk_action_group_add_actions (actgrp, entries, G_N_ELEMENTS (entries), NULL);


    uimgr = gtk_ui_manager_new ();
    gtk_ui_manager_insert_action_group (uimgr, actgrp, 0);


    accgrp = gtk_ui_manager_get_accel_group (uimgr);
    gtk_window_add_accel_group (GTK_WINDOW (window), accgrp);


    if (!gtk_ui_manager_add_ui_from_string (uimgr, menu_desc, -1, &error)) {
        g_print (_("Failed to build menubar: %s"), error->message);
        g_error_free (error);

        return NULL;
    }


    menubar = gtk_ui_manager_get_widget (uimgr, "/GpredictMenu");

    return menubar;
}
