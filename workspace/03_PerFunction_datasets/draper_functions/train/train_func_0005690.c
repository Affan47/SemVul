CrossingsTest( double pgon[][2], int numverts, double point[2] )
{
#ifdef	WINDING
register int	crossings ;
#endif
register int	j, yflag0, yflag1, inside_flag, xflag0 ;
register double ty, tx, *vtx0, *vtx1 ;
#ifdef	CONVEX
register int	line_flag ;
#endif

    tx = point[XCOORD] ;
    ty = point[YCOORD] ;

    vtx0 = pgon[numverts-1] ;

    yflag0 = ( vtx0[YCOORD] >= ty ) ;
    vtx1 = pgon[0] ;

#ifdef	WINDING
    crossings = 0 ;
#else
    inside_flag = 0 ;
#endif
#ifdef	CONVEX
    line_flag = 0 ;
#endif
    for ( j = numverts+1 ; --j ; ) {

	yflag1 = ( vtx1[YCOORD] >= ty ) ;


	if ( yflag0 != yflag1 ) {
	    xflag0 = ( vtx0[XCOORD] >= tx ) ;


	    if ( xflag0 == ( vtx1[XCOORD] >= tx ) ) {


#ifdef	WINDING
		if ( xflag0 ) crossings += ( yflag0 ? -1 : 1 ) ;
#else
		if ( xflag0 ) inside_flag = !inside_flag ;
#endif
	    } else {


		if ( (vtx1[XCOORD] - (vtx1[YCOORD]-ty)*
		     ( vtx0[XCOORD]-vtx1[XCOORD])/(vtx0[YCOORD]-vtx1[YCOORD])) >= tx ) {
#ifdef	WINDING
		    crossings += ( yflag0 ? -1 : 1 ) ;
#else
		    inside_flag = !inside_flag ;
#endif
		}
	    }
#ifdef	CONVEX

	    if ( line_flag ) goto Exit ;


	    line_flag = TRUE ;
#endif
	}


	yflag0 = yflag1 ;
	vtx0 = vtx1 ;
	vtx1 += 2 ;
    }
#ifdef	CONVEX
    Exit: ;
#endif
#ifdef	WINDING

    inside_flag = (crossings != 0) ;
#endif

    return( inside_flag ) ;
}
