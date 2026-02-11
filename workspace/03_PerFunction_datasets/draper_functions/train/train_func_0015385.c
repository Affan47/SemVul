DelDBClicked(GtkButton * UNUSED(button), gpointer dbList)
{
    char *db = GetSelectedDB(GTK_TREE_VIEW(dbList));
    if (db && GetInputYN(_("Are you sure you want to delete all the matches in this database?"))) {
        DBProvider *pdb = GetSelectedDBType();

        if (pdb
            && pdb->DeleteDatabase(db, gtk_entry_get_text(GTK_ENTRY(user)), gtk_entry_get_text(GTK_ENTRY(password)),
                                   gtk_entry_get_text(GTK_ENTRY(hostname)))) {
            gtk_list_store_remove(GTK_LIST_STORE(dbStore), &selected_iter);
            optionsValid = FALSE;
            gtk_widget_set_sensitive(deldb, FALSE);
            gtk_label_set_text(GTK_LABEL(helptext), _("Database successfully removed"));
            pdb->database = "gnubg";
        } else
            gtk_label_set_text(GTK_LABEL(helptext), _("Failed to delete database!"));
    }
}
