gnc_general_search_grab_focus (GNCGeneralSearch *gsl)
{
    g_assert(gsl);
    g_assert(gsl->entry);
    gtk_widget_grab_focus(gsl->entry);
}
