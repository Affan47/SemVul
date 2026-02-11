OGR_F_SetGeometry( OGRFeatureH hFeat, OGRGeometryH hGeom )

{
    VALIDATE_POINTER1( hFeat, "OGR_F_SetGeometry", CE_Failure );

    return ((OGRFeature *) hFeat)->SetGeometry((OGRGeometry *) hGeom);
}
