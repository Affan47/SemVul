doCommand()
{
    QVector<RideFilePoint *> newPoints;
    foreach (RideFilePoint point, points) {
        RideFilePoint *p = new RideFilePoint(point);
        newPoints.append(p);
    }
    ride->appendPoints(newPoints);
    return true;
}
