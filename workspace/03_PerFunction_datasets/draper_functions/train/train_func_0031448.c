on_size_allocate( GtkWidget* widget, GtkAllocation    *allocation )
{
    GTK_WIDGET_CLASS(main_win_parent_class)->size_allocate( widget, allocation );
#if GTK_CHECK_VERSION(2, 20, 0)
    if(gtk_widget_get_realized (widget) )
#else
    if( GTK_WIDGET_REALIZED (widget) )
#endif
    {
        MainWin* mw = (MainWin*)widget;

        if( mw->zoom_mode == ZOOM_FIT )
        {
            while(gtk_events_pending ())
                gtk_main_iteration();

            main_win_fit_window_size( mw, FALSE, GDK_INTERP_BILINEAR );
        }
    }
}
