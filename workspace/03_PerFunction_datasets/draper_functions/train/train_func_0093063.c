read( istream& figfile )
{
    LineFillStyle lfstmp;
    lfstmp.read( figfile, sub_type, depth, true );
    figfile >> cap_style
            >> radius
            >> forward_arrow
            >> backward_arrow
            >> npoints;

    keep_range( sub_type,       "poly sub_type", 1, 5 );
    if( sub_type == 1 )
        keep_range( cap_style,  "poly(polyline) cap_style", 0, 2 );
    if( sub_type == 4 )
        keep_range( radius,         "poly(arc-box) radius",  0 );
    keep_range( forward_arrow,  "poly forward_arrow",  0, 1 );
    keep_range( backward_arrow, "poly backward_arrow", 0, 1 );

    if( npoints<1 || npoints>65536 ) {
        ostringstream err;
        err << "Bad number of polygon points " << npoints
            << " (accepted range = [1,65536]).";
        throw err.str();
    }

    if( forward_arrow != 0 )
        lfstmp.read_arrow( figfile, true );
    if( backward_arrow != 0 )
        lfstmp.read_arrow( figfile, false );
    if( sub_type == 5 ) {
        figfile >> flipped >> file;
    }
    x = new float[npoints];
    y = new float[npoints];
    for( int i=0; i<npoints; ++i )
        figfile >> x[i] >> y[i];

    lfs = linefillstyles.insert( lfstmp ).first;
    if( sub_type == 1 ) {
        lfs->stylename_line();
        if( lfs->area_fill != -1 )
            lfs->stylename_fill();
    } else {
        lfs->stylename();
    }

    return figfile;
}
