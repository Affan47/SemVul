PyFFContour_compare(PyFF_Contour *self,PyObject *other) {
    const double pt_err = .5, spline_err = 1;
    int i,ret;

    ret = PyFFContour_docompare(self,other,pt_err,spline_err);
    if ( !(ret&SS_NoMatch) )
return( 0 );


    if ( self->pt_cnt < ((PyFF_Contour *) other)->pt_cnt )
return( -1 );
    else if ( self->pt_cnt > ((PyFF_Contour *) other)->pt_cnt )
return( 1 );


    for ( i=0; i<self->pt_cnt; ++i ) {
	ret = PyFFPoint_compare(self->points[i],(PyObject *) (((PyFF_Contour *) other)->points[i]) );
	if ( ret!=0 )
return( ret );
    }
return( -1 );
}
