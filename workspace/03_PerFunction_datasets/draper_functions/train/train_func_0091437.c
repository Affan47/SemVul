SetSpatialFilter( OGRGeometry * poGeomIn )

{
    if( !InstallFilter(poGeomIn) )
        return;

    if( m_poFilterGeom != NULL )
    {
        DGNSetSpatialFilter( hDGN,
                             m_sFilterEnvelope.MinX,
                             m_sFilterEnvelope.MinY,
                             m_sFilterEnvelope.MaxX,
                             m_sFilterEnvelope.MaxY );
    }
    else
    {
        DGNSetSpatialFilter( hDGN, 0.0, 0.0, 0.0, 0.0 );
    }

    ResetReading();
}
