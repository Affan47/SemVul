setCoordinate(const QGeoCoordinate &coordinate)
{
    if (origin() != coordinate) {
        setOrigin(coordinate);
        emit coordinateChanged(coordinate);
    }
}
