OptionsWindow_Save_Button (void)
{
    if (!Check_Config()) return;

#ifndef G_OS_WIN32

    Add_String_To_Combo_List(DefaultPathModel,      gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(DefaultPathToMp3)))));
    Add_String_To_Combo_List(FilePlayerModel,       gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(FilePlayerCombo)))));
    Add_String_To_Combo_List(DefaultCommentModel,   gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(DefaultComment)))));
    Add_String_To_Combo_List(CddbLocalPathModel,    gtk_entry_get_text(GTK_ENTRY(gtk_bin_get_child(GTK_BIN(CddbLocalPath)))));
#endif

    Save_Changes_Of_Preferences_Window();

    OptionsWindow_Quit();
    Statusbar_Message(_("Configuration saved"),TRUE);
}
