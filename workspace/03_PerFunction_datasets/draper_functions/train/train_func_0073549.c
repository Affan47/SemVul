GetFeatureCount (int bForce)
{

    if( m_poFilterGeom != NULL || m_poAttrQuery != NULL || bForce)
        return OGRLayer::GetFeatureCount( bForce );
    else
        return m_nLastFeatureId;
}
