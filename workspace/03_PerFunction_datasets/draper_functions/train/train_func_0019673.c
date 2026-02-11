coordinateToWorldReferencePosition(double lng, double lat) const
{
    lng = lng / 360.0 + 0.5;

    lat = 0.5 - (log(tan((PI / 4.0) + (PI / 2.0) * lat / 180.0)) / PI) / 2.0;
    lat = qMax(0.0, lat);
    lat = qMin(1.0, lat);

    const double x = lng * worldReferenceSize.width();
    const double y = lat * worldReferenceSize.height();

    const QPoint r(int(x > 0 ? x + 0.5 : x - 0.5),
                   int(y > 0 ? y + 0.5 : y - 0.5));
    return r;
}
