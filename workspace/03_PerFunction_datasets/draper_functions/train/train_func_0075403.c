GetFeatureCount( int bForce )

{
    if( m_nTotalShapeCount == -1)
    {
        m_nTotalShapeCount = OGRLayer::GetFeatureCount( bForce );
    }

    return m_nTotalShapeCount;
}
