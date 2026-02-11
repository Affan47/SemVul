image_view_set_adjustments( ImageView* iv, GtkAdjustment* h, GtkAdjustment* v )
{
    if( iv->hadj != h )
    {
        if( iv->hadj )
            g_object_unref( iv->hadj );
        if( G_LIKELY(h) )
        {
    #if GTK_CHECK_VERSION( 2, 10, 0 )
            iv->hadj = (GtkAdjustment*)g_object_ref_sink( h );
    #else
            iv->hadj = (GtkAdjustment*)h;
            gtk_object_sink( (GtkObject*)h );
    #endif
        }
        else
            iv->hadj = NULL;
    }
    if( iv->vadj != v )
    {
        if( iv->vadj )
            g_object_unref( iv->vadj );
        if( G_LIKELY(v) )
        {
#if GTK_CHECK_VERSION( 2, 10, 0 )
            iv->vadj = (GtkAdjustment*)g_object_ref_sink( v );
#else
            iv->vadj = (GtkAdjustment*)v;
            gtk_object_sink( (GtkObject*)v );
#endif
        }
        else
            iv->vadj = NULL;
    }
}
