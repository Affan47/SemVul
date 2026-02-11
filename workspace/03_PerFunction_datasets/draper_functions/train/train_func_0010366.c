OGR_G_RemoveGeometry( OGRGeometryH hGeom, int iGeom, int bDelete )

{
    VALIDATE_POINTER1( hGeom, "OGR_G_RemoveGeometry", 0 );

    switch( wkbFlatten(((OGRGeometry *) hGeom)->getGeometryType()) )
    {
      case wkbPolygon:
      {
          CPLError( CE_Failure, CPLE_AppDefined,
                    "OGR_G_RemoveGeometry() not supported on polygons yet." );
          return OGRERR_UNSUPPORTED_OPERATION;
      }

      case wkbMultiPoint:
      case wkbMultiLineString:
      case wkbMultiPolygon:
      case wkbGeometryCollection:
        return ((OGRGeometryCollection *)hGeom)->removeGeometry( iGeom,bDelete);

      default:
        return OGRERR_UNSUPPORTED_OPERATION;
    }
}
