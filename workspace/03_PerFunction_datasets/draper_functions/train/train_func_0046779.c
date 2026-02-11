draw_box( FL_OBJECT * ob,
          int         ev,
          FL_Coord    x   FL_UNUSED_ARG,
          FL_Coord    y   FL_UNUSED_ARG,
          int         k   FL_UNUSED_ARG,
          void      * sp  FL_UNUSED_ARG )
{
    int p = ( FL_max( ob->w, ob->h ) / 2 ) * 2 + 1;

    if ( ev != FL_DRAW )
        return 0;

    fl_winset( FL_ObjWin( ob ) );

    if ( ! fli_dithered( fl_vmode ) )
    {
        fl_color( FL_YELLOW );
        fli_reset_vertex( );
        fli_box_vert( ob->x, ob->y, p, p );
        fli_endpolygon( );
    }
    fl_linewidth( 2 );
    fl_color( FL_BLACK );
    fli_reset_vertex( );
    fli_box_vert( ob->x, ob->y, ob->w, ob->h );
    fli_endclosedline( );
    fl_linewidth( 0 );

    return 0;
}
