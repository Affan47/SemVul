rmPoint(int x, int y)
{
    pointIterator minI;

    minI = findClosestPoint(x,y);

    if (minI != pointlist.end()) {

        mainViewer->remove(*minI);

        mainViewer->deletePoint((*minI).x(), (*minI).y());

        pointlist.erase(minI);

        redrawLines();

        hasChanged = true;
    }
}
