gsb_gui_hpaned_size_allocate ( GtkWidget *hpaned,
                        GtkAllocation *allocation,
                        gpointer null )
{
    gint paned_width;

    paned_width = gtk_paned_get_position ( GTK_PANED ( hpaned ) );

    if ( paned_width  < mini_paned_width )
        gtk_paned_set_position ( GTK_PANED ( hpaned ), mini_paned_width );

    return FALSE;
}
