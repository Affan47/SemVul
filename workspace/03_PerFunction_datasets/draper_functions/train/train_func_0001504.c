fl_finish( void )
{


    if ( ! flx->display )
        return;

    XChangeKeyboardControl( flx->display, fli_keybdmask,
                            &fli_keybdcontrol );

    fl_remove_all_signal_callbacks( );
    fl_remove_all_timeouts( );


    while ( fli_int.formnumb > 0 )
        fl_hide_form( fli_int.forms[ 0 ] );


    while ( fli_int.hidden_formnumb > 0 )
    {
        if (    fli_int.hidden_formnumb > 1
             && fli_is_tooltip_form( fli_int.forms[ 0 ] ) )
            fl_free_form( fli_int.forms[ 1 ] );
        else
            fl_free_form( fli_int.forms[ 0 ] );
    }


    fli_obj_queue_delete( );
    fli_event_queue_delete( );


    fli_free_xtext_workmem( );


    fli_release_symbols( );


    fli_goodies_cleanup( );


    fli_free_fselectors( );


    fli_popup_finish( );


    fli_free_cmdline_args( );


    fli_free_cursors( );


    fli_free_colormap( fl_vmode );


#ifdef XlibSpecificationRelease
    if ( fli_context && XSupportsLocale( ) && fli_context->xim )
    {
        if ( fli_context->xic )
            XDestroyIC( fli_context->xic );
        XCloseIM( fli_context->xim );
    }
#endif

    fl_safe_free( fli_context );


    XCloseDisplay( flx->display );
    flx->display = fl_display = None;
}
