childAdded(QGeoMapObject *childObject)
{
    if (!childObject)
        return;

    QGeoTiledMapObjectInfo* info = static_cast<QGeoTiledMapObjectInfo*>(childObject->info());
    if (info && info->graphicsItem) {


        childObject->disconnect(childObject, SIGNAL(zValueChanged(int)), info, SLOT(zValueChanged(int)));
        info->graphicsItem->setParentItem(graphicsItem);
        tiledMapDataPrivate->update(mapObject());

    }
}
