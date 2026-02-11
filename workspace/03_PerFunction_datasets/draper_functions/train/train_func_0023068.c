handle_nmenu( FL_OBJECT * obj,
              int         event,
              FL_Coord    mx   FL_UNUSED_ARG,
              FL_Coord    my   FL_UNUSED_ARG,
              int         key  FL_UNUSED_ARG,
              void      * ev   FL_UNUSED_ARG )
{
    FLI_NMENU_SPEC *sp = obj->spec;
    unsigned int w,
                 h;
    int ret = FL_RETURN_NONE;

    switch ( event )
    {
        case FL_DRAW :
            draw_menu( obj );
            break;

        case FL_ENTER :
            if ( ! IS_TOUCH_NMENU( obj ) )
                break;


        case FL_SHORTCUT :
        case FL_PUSH :
            if ( ! sp->popup || ! sp->popup->entries )
                break;
            obj->pushed = 1;
            fl_redraw_object( obj );
            fl_popup_get_size( sp->popup, &w, &h );
            if ( obj->form->y + obj->y + obj->h + h < ( unsigned int ) fl_scrh )
                fl_popup_set_position( sp->popup,
                                       obj->form->x + obj->x,
                                       obj->form->y + obj->y + obj->h );
            else
                fl_popup_set_position( sp->popup,
                                       obj->form->x + obj->x,
                                       obj->form->y + obj->y - h );
            sp->sel = fl_popup_do( sp->popup );
            obj->pushed = 0;
            fl_redraw_object( obj );
            if ( sp->sel != NULL )
                ret |= FL_RETURN_CHANGED | FL_RETURN_END;
            break;

        case FL_FREEMEM :
            if ( sp && sp->popup )
                fl_popup_delete( sp->popup );
            fl_safe_free( obj->spec );
            break;
    }

    return ret;
}
