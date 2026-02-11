OGR_G_GetPoint( OGRGeometryH hGeom, int i,
                     double *pdfX, double *pdfY, double *pdfZ )

{
    VALIDATE_POINTER0( hGeom, "OGR_G_GetPoint" );

    switch( wkbFlatten(((OGRGeometry *) hGeom)->getGeometryType()) )
    {
      case wkbPoint:
      {
          if( i == 0 )
          {
              *pdfX = ((OGRPoint *)hGeom)->getX();
              *pdfY = ((OGRPoint *)hGeom)->getY();
              if( pdfZ != NULL )
                  *pdfZ = ((OGRPoint *)hGeom)->getZ();
          }
          else
          {
              CPLError(CE_Failure, CPLE_NotSupported, "Only i == 0 is supported");
          }
      }
      break;

      case wkbLineString:
      {
          OGRLineString* poLS = (OGRLineString *) hGeom;
          if (i < 0 || i >= poLS->getNumPoints())
          {
              CPLError(CE_Failure, CPLE_NotSupported, "Index out of bounds");
              *pdfX = *pdfY = 0;
              if( pdfZ != NULL )
                  *pdfZ = 0;
          }
          else
          {
            *pdfX = poLS->getX( i );
            *pdfY = poLS->getY( i );
            if( pdfZ != NULL )
                *pdfZ =  poLS->getZ( i );
          }
      }
      break;

      default:
        CPLError(CE_Failure, CPLE_NotSupported, "Incompatible geometry for operation");
        break;
    }
}
