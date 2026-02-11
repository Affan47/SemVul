ege_color_prof_tracker_new( GtkWidget* target )
{
    GObject* obj = (GObject*)g_object_new( EGE_COLOR_PROF_TRACKER_TYPE,
                                           NULL );

    EgeColorProfTracker* tracker = EGE_COLOR_PROF_TRACKER( obj );
    tracker->private_data->_target = target;

    if ( target ) {
        g_object_weak_ref( G_OBJECT(target), target_finalized, obj );
        g_signal_connect( G_OBJECT(target), "hierarchy-changed", G_CALLBACK( target_hierarchy_changed_cb ), obj );
        g_signal_connect( G_OBJECT(target), "screen-changed", G_CALLBACK( target_screen_changed_cb ), obj );


        target_hierarchy_changed_cb( target, 0, obj );
        target_screen_changed_cb( target, 0, obj );
    } else {
        abstract_trackers = g_slist_append( abstract_trackers, obj );

        GSList* curr = tracked_screens;
        while ( curr ) {
            ScreenTrack* track = (ScreenTrack*)curr->data;
            gint screenNum = gdk_screen_get_number(track->screen);
            gint monitor = 0;
            for ( monitor = 0; monitor < (gint)track->profiles->len; monitor++ ) {
                g_signal_emit( G_OBJECT(tracker), signals[MODIFIED], 0, screenNum, monitor );
            }

            curr = g_slist_next(curr);
        }

    }

    return tracker;
}
