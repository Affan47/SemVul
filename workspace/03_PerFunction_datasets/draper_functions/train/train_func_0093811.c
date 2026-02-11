draw_chart( FL_OBJECT * ob )
{
    FLI_CHART_SPEC *sp = ob->spec;
    FL_Coord absbw = FL_abs( ob->bw );
    float min = sp->min,
          max = sp->max;
    int i;


    sp->x = ob->x + 3 + 2 * absbw;
    sp->y = ob->y + 3 + 2 * absbw;
    sp->w = ob->w - 6 - 4 * absbw;
    sp->h = ob->h - 6 - 4 * absbw;


    if ( min == max )
    {
        min = max = sp->numb ? sp->entries[ 0 ].val : 0.0;
        for ( i = 0; i < sp->numb; i++ )
        {
            if ( sp->entries[ i ].val < min )
                min = sp->entries[ i ].val;
            if ( sp->entries[ i ].val > max )
                max = sp->entries[ i ].val;
        }
    }


    if ( min == max )
    {
        min -= 1.0;
        max += 1.0;
    }


    fl_drw_box( ob->boxtype, ob->x, ob->y, ob->w, ob->h, ob->col1, ob->bw );

    if ( sp->numb == 0 )
    {
        fl_drw_text_beside( ob->align, ob->x, ob->y, ob->w, ob->h,
                            ob->lcol, ob->lstyle, ob->lsize, ob->label );
        return;
    }

    fl_set_clipping( sp->x - 1, sp->y - 1, sp->w + 2, sp->h + 2 );

    switch ( ob->type )
    {
        case FL_BAR_CHART:
            draw_barchart( sp, min, max );
            break;

        case FL_HORBAR_CHART:
            draw_horbarchart( sp, min, max );
            break;

        case FL_PIE_CHART:
            draw_piechart( sp, 0 );
            break;

        case FL_SPECIALPIE_CHART:
            draw_piechart( sp, 1 );
            break;

        default:
            draw_linechart( ob->type, sp, min, max );
            break;
    }

    fl_unset_clipping( );
}
