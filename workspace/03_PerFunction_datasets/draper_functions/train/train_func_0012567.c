GetFeatureCount( int bForce )
{
    if (poReader == NULL && m_poFilterGeom == NULL && m_poAttrQuery == NULL)
    {
        poDS->ReadWholeFileIfNecessary();
        return nFeatureArraySize;
    }
    else
        return OGRLayer::GetFeatureCount( bForce ) ;
}
