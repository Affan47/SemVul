GetFeature(long nFeatureId)
{
    OGRFeature *poFeatureRef;

    poFeatureRef = GetFeatureRef(nFeatureId);
    if (poFeatureRef)
    {

        CPLAssert(poFeatureRef == m_poCurFeature);
        m_poCurFeature = NULL;

        return poFeatureRef;
    }
    else
      return NULL;
}
