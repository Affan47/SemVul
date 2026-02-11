EqualAirwayIntersectionFeatureFunc(const void* _feature1, const void* _feature2)
{
    OGRFeature* feature1 = (OGRFeature*)_feature1;
    OGRFeature* feature2 = (OGRFeature*)_feature2;
    if (strcmp(feature1->GetFieldAsString(0), feature2->GetFieldAsString(0)) == 0)
    {
        OGRPoint* point1 = (OGRPoint*) feature1->GetGeometryRef();
        OGRPoint* point2 = (OGRPoint*) feature2->GetGeometryRef();
        return (point1->getX() == point2->getX() && point1->getY() == point2->getY());
    }
    return FALSE;
}
