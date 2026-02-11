invalidateObject(QGeoMapObject *obj)
{


    updateLatLonTransform(obj);

    const QRectF view = latLonViewport().boundingRect();

    bool needsPixelUpdate = false;
    foreach (QGraphicsItem *item, latLonItemsRev.values(obj)) {
        if (item->boundingRect().intersects(view)) {
            needsPixelUpdate = true;
            break;
        }
    }

    if (needsPixelUpdate) {
        objectsForPixelUpdate << obj;
        mdp->emitUpdateMapDisplay();
    }
}
