updateTransforms()
{
    bool groupUpdated = false;

    foreach (QGeoMapObject *obj, objectsForLatLonUpdate) {
        QGeoMapGroupObject *group = qobject_cast<QGeoMapGroupObject*>(obj);
        if (group) {
            updateLatLonsForGroup(group);
            groupUpdated = true;
        } else {
            updateLatLonTransform(obj);
        }
    }

    objectsForLatLonUpdate.clear();

    foreach (QGeoMapObject *obj, objectsForPixelUpdate) {
        QGeoMapGroupObject *group = qobject_cast<QGeoMapGroupObject*>(obj);
        if (group) {
            updatePixelsForGroup(group);
            groupUpdated = true;
        } else {
            updatePixelTransform(obj);
        }
    }

    objectsForPixelUpdate.clear();

    if (groupUpdated)
        rebuildScenes();
}
