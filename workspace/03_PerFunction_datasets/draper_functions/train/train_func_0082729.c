layoutContainments()
{
    if (CoronaPrivate::s_positioningContainments) {
        return;
    }

    CoronaPrivate::s_positioningContainments = true;


    QList<Containment*> c = containments();
    QMutableListIterator<Containment*> it(c);

    while (it.hasNext()) {
        Containment *containment = it.next();
        if (containment->containmentType() == Containment::PanelContainment ||
            containment->containmentType() == Containment::CustomPanelContainment ||
            offscreenWidgets().contains(containment)) {


            it.remove();
            continue;
        }
    }

    qSort(c.begin(), c.end(), containmentSortByPosition);

    if (c.isEmpty()) {
        CoronaPrivate::s_positioningContainments = false;
        return;
    }

    int column = 0;
    int x = 0;
    int y = 0;
    int rowHeight = 0;

    it.toFront();
    while (it.hasNext()) {
        Containment *containment = it.next();
        containment->setPos(x, y);


        int height = containment->size().height();
        if (height > rowHeight) {
            rowHeight = height;
        }

        ++column;

        if (column == CONTAINMENT_COLUMNS) {
            column = 0;
            x = 0;
            y += rowHeight + INTER_CONTAINMENT_MARGIN + TOOLBOX_MARGIN;
            rowHeight = 0;
        } else {
            x += containment->size().width() + INTER_CONTAINMENT_MARGIN;
        }


    }

    CoronaPrivate::s_positioningContainments = false;
}
