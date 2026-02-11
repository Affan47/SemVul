handle_scrollbar( FL_OBJECT * obj,
                  int         event,
                  FL_Coord    mx   FL_UNUSED_ARG,
                  FL_Coord    my   FL_UNUSED_ARG,
                  int         key  FL_UNUSED_ARG,
                  void      * ev   FL_UNUSED_ARG )
{
    switch ( event )
    {
        case FL_ATTRIB :
        case FL_RESIZED :
            attrib_change( obj );
            get_geom( obj );
            break;

        case FL_DRAW :
            if ( IsThin( obj->type ) )
                fl_drw_box( obj->boxtype, obj->x, obj->y, obj->w, obj->h,
                            obj->col1, obj->bw );


        case FL_DRAWLABEL :
            if ( obj->label && *obj->label )
                fl_draw_object_label_outside( obj );
            break;

        case FL_FREEMEM :

            fl_free( obj->spec );
            break;
    }

    return FL_RETURN_NONE;
}
