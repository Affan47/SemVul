toggle_logging_pause_resume(gboolean currentlyLogging)
{
    if (currentlyLogging)
    {
        gtk_menu_item_set_label(GTK_MENU_ITEM(log_pause_resume_menu), _("Pause"));
    }
    else
    {
        gtk_menu_item_set_label(GTK_MENU_ITEM(log_pause_resume_menu), _("Resume"));
    }
}
