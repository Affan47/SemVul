handle_tabfolder( FL_OBJECT * ob,
                  int         event,
                  FL_Coord    mx   FL_UNUSED_ARG,
                  FL_Coord    my   FL_UNUSED_ARG,
                  int         key  FL_UNUSED_ARG,
                  void      * ev )
{
    FL_FORM *folder;
    FLI_TABFOLDER_SPEC *sp = ob->spec;

    switch ( event )
    {
        case FL_RESIZED:
            if (    ( folder = fl_get_active_folder( ob ) )
                 && sp->auto_fit != FL_NO )
            {
                if ( sp->auto_fit == FL_FIT )
                    fl_set_form_size( folder, sp->canvas->w, sp->canvas->h );
                else if (    folder->w < sp->canvas->w
                          || folder->h < sp->canvas->h )
                    fl_set_form_size( folder, sp->canvas->w, sp->canvas->h );
            }
            break;

        case FL_MOVEORIGIN:
            if ( ( folder = fl_get_active_folder( ob ) ) )
            {
                fl_get_winorigin( folder->window, &folder->x, &folder->y );


                fli_handle_form( folder, FL_MOVEORIGIN, 0, ev );
            }
            break;

        case FL_ATTRIB:
        case FL_DRAW:
            fl_set_object_boxtype( sp->canvas,
                                   fli_boxtype2frametype( ob->boxtype ) );
            sp->processing_destroy = 0;
            compute_position( ob );
            break;

        case FL_FREEMEM:
            fl_safe_free( sp->forms );
            fl_safe_free( sp->title );
            fl_free( sp );
            break;
    }

    return 0;
}
