DGNGetRawExtents( DGNInfo *psDGN, int nType, unsigned char *pabyRawData,
                  GUInt32 *pnXMin, GUInt32 *pnYMin, GUInt32 *pnZMin,
                  GUInt32 *pnXMax, GUInt32 *pnYMax, GUInt32 *pnZMax )

{
    if( pabyRawData == NULL )
        pabyRawData = psDGN->abyElem + 0;

    switch( nType )
    {
      case DGNT_LINE:
      case DGNT_LINE_STRING:
      case DGNT_SHAPE:
      case DGNT_CURVE:
      case DGNT_BSPLINE_POLE:
      case DGNT_BSPLINE_SURFACE_HEADER:
      case DGNT_BSPLINE_CURVE_HEADER:
      case DGNT_ELLIPSE:
      case DGNT_ARC:
      case DGNT_TEXT:
      case DGNT_TEXT_NODE:
      case DGNT_COMPLEX_CHAIN_HEADER:
      case DGNT_COMPLEX_SHAPE_HEADER:
      case DGNT_CONE:
      case DGNT_3DSURFACE_HEADER:
      case DGNT_3DSOLID_HEADER:
        *pnXMin = DGN_INT32( pabyRawData + 4 );
        *pnYMin = DGN_INT32( pabyRawData + 8 );
        if( pnZMin != NULL )
            *pnZMin = DGN_INT32( pabyRawData + 12 );

        *pnXMax = DGN_INT32( pabyRawData + 16 );
        *pnYMax = DGN_INT32( pabyRawData + 20 );
        if( pnZMax != NULL )
            *pnZMax = DGN_INT32( pabyRawData + 24 );
        return TRUE;

      default:
        return FALSE;
    }
}
