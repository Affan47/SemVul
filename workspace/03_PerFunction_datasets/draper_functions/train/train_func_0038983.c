resize_selection( FL_Coord dx,
                  FL_Coord dy )
{
    float x,
          y,
          w,
          h,
          ox,
          oy,
          ow,
          oh;
    float yscale,
          xscale;
    int i;

    if ( ! cur_form || selnumb == 0 )
        return;

    compute_selbox(&x, &y, &w, &h);

    ox = x;
    oy = y;
    ow = w;
    oh = h;

    if ( backf )
    {
        winw = fl_scrw;
        winh = fl_scrh;
    }

    if ( ( w += dx ) > winw)
        w = winw;
    else if ( w < MINSIZE )
        w = MINSIZE;

    if ( ( h += dy ) > winh )
        h = winh;
    else if ( h < MINSIZE )
        h = MINSIZE;

    if ( w == ow && oh == h )
        return;

    xscale = ( float ) w / ow;
    yscale = ( float ) h / oh;


    for ( i = 0; i < selnumb; i++ )
        if (    selobj[ i ]->objclass != FL_BEGIN_GROUP
             && selobj[ i ]->objclass != FL_END_GROUP )
        {
            selobj[ i ]->fl1 -= ox;
            selobj[ i ]->fl2 -= ox;
            selobj[ i ]->fr1 += ox;
            selobj[ i ]->fr2 += ox;

            selobj[ i ]->ft1 -= oy;
            selobj[ i ]->ft2 -= oy;
            selobj[ i ]->fb1 += oy;
            selobj[ i ]->fb2 += oy;

            fl_scale_object( selobj[ i ], xscale, yscale );

            selobj[ i ]->x = selobj[ i ]->fl1 += x;
            selobj[ i ]->fl2 += x;
            selobj[ i ]->fr1 -= x;
            selobj[ i ]->fr2 -= x;

            selobj[ i ]->y = selobj[ i ]->ft1 += y;
            selobj[ i ]->ft2 += y;
            selobj[ i ]->fb1 -= y;
            selobj[ i ]->fb2 -= y;

            fl_notify_object( selobj[ i ], FL_RESIZED );
        }

    if ( backf )
    {
        cur_form->w_hr = cur_form->w = selobj[ 0 ]->w;
        cur_form->h_hr = cur_form->h = selobj[ 0 ]->h;
        fl_winresize( main_window, cur_form->w, cur_form->h );
    }

    redraw_the_form( 1 );
    changed = FL_TRUE;
}
