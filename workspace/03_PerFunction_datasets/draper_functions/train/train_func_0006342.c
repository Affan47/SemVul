fl_set_object_bw( FL_OBJECT * obj,
                  int         bw )
{


    if ( FL_abs( bw ) > FL_MAX_BW )
        bw = bw > 0 ? FL_MAX_BW : - FL_MAX_BW;

    if ( bw == 0 )
        bw = -1;

    if ( ! obj )
    {
        M_err( "fl_set_object_bw", "NULL object" );
        return;
    }


    if ( obj->objclass == FL_BEGIN_GROUP )
    {
        fl_freeze_form( obj->form );
        for ( ; obj && obj->objclass != FL_END_GROUP; obj = obj->next )
        {
            if ( obj->bw != bw )
            {
                obj->bw = bw;
                if ( obj->objclass != FL_BEGIN_GROUP )
                {
                    fli_handle_object( obj, FL_ATTRIB, 0, 0, 0, NULL, 0 );
                    fl_redraw_object( obj );
                }
            }
        }

        fl_unfreeze_form( obj->form );
    }
    else if ( obj->bw != bw )
    {
        obj->bw = bw;
        fli_handle_object( obj, FL_ATTRIB, 0, 0, 0, NULL, 0 );
        fl_redraw_object( obj );
    }
}
