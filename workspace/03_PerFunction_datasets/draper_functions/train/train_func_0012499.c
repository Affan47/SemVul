greaterThan(const QString &v1, const QString &v2) const
{
    int majorV1 = -1;
    int minorV1 = -1;
    transformVersion(v1, &majorV1, &minorV1);

    int majorV2 = -1;
    int minorV2 = -1;
    transformVersion(v2, &majorV2, &minorV2);

    return  (majorV1 > majorV2
             || (majorV1 == majorV2 && minorV1 > minorV2));
}
