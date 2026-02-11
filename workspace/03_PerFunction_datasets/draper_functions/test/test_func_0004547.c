OGR_G_GetPoints( OGRGeometryH hGeom,
                     void* pabyX, int nXStride,
                     void* pabyY, int nYStride,
                     void* pabyZ, int nZStride)
{
    VALIDATE_POINTER1( hGeom, "OGR_G_GetPoints", 0 );

    switch( wkbFlatten(((OGRGeometry *) hGeom)->getGeometryType()) )
    {
      case wkbPoint:
      {
        if (pabyX) *((double*)pabyX) = ((OGRPoint *)hGeom)->getX();
        if (pabyY) *((double*)pabyY) = ((OGRPoint *)hGeom)->getY();
        if (pabyZ) *((double*)pabyZ) = ((OGRPoint *)hGeom)->getZ();
        return 1;
      }
      break;

      case wkbLineString:
      {
          OGRLineString* poLS = (OGRLineString *) hGeom;
          poLS->getPoints(pabyX, nXStride, pabyY, nYStride, pabyZ, nZStride);
          return poLS->getNumPoints();
      }
      break;

      default:
        CPLError(CE_Failure, CPLE_NotSupported, "Incompatible geometry for operation");
        return 0;
        break;
    }
}
