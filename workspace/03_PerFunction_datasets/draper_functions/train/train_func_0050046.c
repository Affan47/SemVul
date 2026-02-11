removeChildObject(QGeoMapObject *childObject)
{
    if (!childObject)
        return;

    if (d_ptr->children.removeAll(childObject) > 0) {

        disconnect(childObject, SIGNAL(zValueChanged(int)),
                   d_ptr, SLOT(childChangedZValue(int)));

        emit childRemoved(childObject);
        childObject->setMapData(0);


    }


}
