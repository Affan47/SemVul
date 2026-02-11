reverseGeocode(const QGeoCoordinate &coordinate,
        QGeoBoundingArea *bounds)
{
    Q_UNUSED(coordinate)
    Q_UNUSED(bounds)
    return new QGeoSearchReply(QGeoSearchReply::UnsupportedOptionError,
                               "Reverse geocoding is not supported by this service provider.", this);
}
