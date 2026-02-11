rmLastPoint(void)
{
    if (!pointlist.empty()) {
        mypoint &aPoint = pointlist.back();
        dbgprintf("Removing last point from current pointfile\n");
        if (!aPoint.isBreak()) {

            mainViewer->deletePoint(aPoint.x(), aPoint.y());
            mainViewer->remove(aPoint);
        } else {


            pointIterator pii;
            int           linesToDelete = 0;

            pii = ----pointlist.end();
            while ((!pii->isBreak()) && (pii != pointlist.begin())) {
                --pii;
                ++linesToDelete;
            }


            if (pii->isBreak()) {
                ++pii;
                --linesToDelete;
            }


            while (linesToDelete-- > 0) {
                mainViewer->remove(linelist.back());
                (linelist.back()).undraw();
                linelist.pop_back();
            }

        }


        pointlist.pop_back();

        hasChanged = true;
    } else {
        dbgprintf("Point list is now empty\n");
    }

    return;
}
