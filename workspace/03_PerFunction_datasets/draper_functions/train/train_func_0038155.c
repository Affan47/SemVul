draw_star( FLIMAGE_MARKER * m )
{
    static int mode = CoordModeOrigin;
    int w = m->w / 2,
        h = m->h / 2;
    int xo = m->x,
        yo = m->y;
    FL_POINT p[ 11 ];
    static FL_FPOINT fp[ 10 ],
                     pp[ 10 ];
    static int first = 1;
    int i;


    if ( first )
    {
        float t,
              l = sin( 18.0 * M_PI / 180.0 ) / sin( 54.0 * M_PI / 180.0 );

        for ( i = 0, t = 54.0; i < 10; i += 2, t += 72.0 )
        {
            fp[ i ].x = l * cos( t * M_PI / 180.0 );
            fp[ i ].y = l * sin( t * M_PI / 180.0 );
        }

        for ( i = 1, t = 90.0; i < 10; i += 2, t += 72.0 )
        {
            fp[ i ].x = cos( t * M_PI / 180.0 );
            fp[ i ].y = sin( t * M_PI / 180.0 );
        }

        first = 0;
    }

    scalef( fp, pp, 10, w, h );
    rotatef( pp, 10, m->angle, 0, 0 );

    for ( i = 0; i < 10; i++ )
    {
        p[ i ].x = xo + pp[i].x + 0.5;
        p[ i ].y = yo - pp[i].y + 0.5;
    }

    fill_point( p[ 10 ], p[ 0 ].x, p[ 0 ].y );

    if ( ! m->fill )
        XDrawLines( m->display, m->win, m->gc, p, 11, mode );
    else
        XFillPolygon( m->display, m->win, m->gc, p, 10, Nonconvex, mode );
}
