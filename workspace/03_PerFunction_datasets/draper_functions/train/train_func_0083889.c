childRemoved(QGeoMapObject *childObject)
{
    if (childObject && tiledMapDataPrivate->oe) {
        tiledMapDataPrivate->oe->removeObject(childObject);
        updateItem();
    }
}
