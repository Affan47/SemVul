GotoState( GLUtesselator *tess, enum TessState newState )
{
  while( tess->state != newState ) {


    if( tess->state < newState ) {
      switch( tess->state ) {
      case T_DORMANT:
	CALL_ERROR_OR_ERROR_DATA( GLU_TESS_MISSING_BEGIN_POLYGON );
	gluTessBeginPolygon( tess, NULL );
	break;
      case T_IN_POLYGON:
	CALL_ERROR_OR_ERROR_DATA( GLU_TESS_MISSING_BEGIN_CONTOUR );
	gluTessBeginContour( tess );
	break;
      default:
	 ;
      }
    } else {
      switch( tess->state ) {
      case T_IN_CONTOUR:
	CALL_ERROR_OR_ERROR_DATA( GLU_TESS_MISSING_END_CONTOUR );
	gluTessEndContour( tess );
	break;
      case T_IN_POLYGON:
	CALL_ERROR_OR_ERROR_DATA( GLU_TESS_MISSING_END_POLYGON );

	MakeDormant( tess );
	break;
      default:
	 ;
      }
    }
  }
}
