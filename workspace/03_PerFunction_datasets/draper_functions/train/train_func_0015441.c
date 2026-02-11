writingProgressUpdaterCbk(VolInfo* volInfo, double percentComplete)
{
    if(GBLWritingProgressBar != NULL)
    {
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(GBLWritingProgressBar), percentComplete / 100);


        while(gtk_events_pending())
            gtk_main_iteration();
    }
}
