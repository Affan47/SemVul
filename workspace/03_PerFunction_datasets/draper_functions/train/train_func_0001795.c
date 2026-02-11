latLonViewport()
{
    QPolygonF view;
    QGeoBoundingBox viewport = md->viewport();
    QGeoCoordinate c, c2;
    double offset = 0.0;

    c = viewport.bottomLeft();
    view << QPointF(c.longitude() * 3600.0, c.latitude() * 3600.0);
    c2 = viewport.bottomRight();
    if (c2.longitude() < c.longitude())
        offset = 360.0 * 3600.0;
    view << QPointF(c2.longitude() * 3600.0 + offset, c2.latitude() * 3600.0);
    c = viewport.topRight();
    view << QPointF(c.longitude() * 3600.0 + offset, c.latitude() * 3600.0);
    c = viewport.topLeft();
    view << QPointF(c.longitude() * 3600.0, c.latitude() * 3600.0);

    return view;
}
