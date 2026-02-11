handle_select( FL_OBJECT * obj,
               int         event,
               FL_Coord    mx   FL_UNUSED_ARG,
               FL_Coord    my   FL_UNUSED_ARG,
               int         key,
               void *      ev   FL_UNUSED_ARG )
{
    FLI_SELECT_SPEC *sp = obj->spec;
    FL_POPUP_RETURN *ret = NULL;
    unsigned int w,
                 h;
    int sret = FL_RETURN_NONE;

    switch ( event )
    {
        case FL_DRAW :
            if ( obj->type != FL_DROPLIST_SELECT )
                draw_select( obj );
            else
                draw_droplist( obj );


        case FL_DRAWLABEL :
            obj->align &= ~ FL_ALIGN_INSIDE;
            fl_drw_text_beside( obj->align & ~ FL_ALIGN_INSIDE, obj->x, obj->y,
                                obj->w, obj->h, obj->lcol, obj->lstyle,
                                obj->lsize, obj->label );
            break;

        case FL_ENTER :
        case FL_LEAVE :
            fl_redraw_object( obj );
            break;

        case FL_SHORTCUT :
            obj->pushed = 1;
            key = FL_MBUTTON1;
            fl_popup_get_size( sp->popup, &w, &h );
            fl_popup_set_position( sp->popup,
                                   obj->form->x + obj->x + ( obj->w - w ) / 2,
                                   obj->form->y + obj->y + obj->h );
            sret |= FL_RETURN_END;


        case FL_PUSH :
            if ( handle_push( obj, key ) )
                sret |= FL_RETURN_CHANGED;
            break;

        case FL_RELEASE :
            if ( key != FL_MBUTTON2 && key != FL_MBUTTON3 )
                break;

            if ( sp->timeout_id != -1 )
            {
                fl_remove_timeout( sp->timeout_id );
                sp->timeout_id = -1;
            }

            fl_redraw_object( obj );
            sret |= FL_RETURN_END;
            break;

        case FL_UPDATE:
            if (    ( key == FL_MBUTTON2 || key == FL_MBUTTON3 )
                 && sp->timeout_id == -1 )
            {
                const FL_POPUP_ENTRY *old_entry = sp->sel ?
                                                  sp->sel->entry : NULL;

                ret = ( key == FL_MBUTTON2 ?
                        find_prev_item : find_next_item )( obj );
                if (    ret != NULL
                     && ret->entry != old_entry
                     && ret->entry->callback
                     && ret->entry->callback( ret ) == FL_IGNORE )
                    ret = NULL;
                fl_redraw_object( obj );
                sp->timeout_id = fl_add_timeout( sp->repeat_ms, timeout_cb,
                                                 sp );
                if ( ret != NULL )
                    sret |= FL_RETURN_CHANGED;
            }
            break;

        case FL_FREEMEM :
            if ( sp && sp->popup )
                fl_popup_delete( sp->popup );
            fl_safe_free( obj->spec );
            break;
    }

    return sret;
}
