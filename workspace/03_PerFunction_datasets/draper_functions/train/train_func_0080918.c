RelationalSaveOptions(void)
{
    if (optionsValid) {
        DBProviderType dbType = (DBProviderType) gtk_combo_box_get_active(GTK_COMBO_BOX(dbtype));
        SetDBSettings(dbType, GetSelectedDB(GTK_TREE_VIEW(dbList)), gtk_entry_get_text(GTK_ENTRY(user)),
                      gtk_entry_get_text(GTK_ENTRY(password)), gtk_entry_get_text(GTK_ENTRY(hostname)));

        storeGameStats = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(gameStats));
    }
}
