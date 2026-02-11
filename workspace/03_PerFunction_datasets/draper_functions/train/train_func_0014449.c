viewport() const
{
    Q_D(const QGeoTiledMapData);
    if (d->worldReferenceViewportRectRight.isValid()) {
        return QGeoBoundingBox(worldReferencePositionToCoordinate(d->worldReferenceViewportRectLeft.topLeft()),
                               worldReferencePositionToCoordinate(d->worldReferenceViewportRectRight.bottomRight()));
    } else {
        return QGeoBoundingBox(worldReferencePositionToCoordinate(d->worldReferenceViewportRect.topLeft()),
                               worldReferencePositionToCoordinate(d->worldReferenceViewportRect.bottomRight()));
    }
}
