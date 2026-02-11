childUpdated(QGeoMapObject *childObject)
{
    if (!childObject)
        return;

    QGeoTiledMapObjectInfo* info = static_cast<QGeoTiledMapObjectInfo*>(childObject->info());
    if (info && info->graphicsItem) {

        tiledMapDataPrivate->update(mapObject());
        info->zValueChanged(childObject->zValue());
    }
}
