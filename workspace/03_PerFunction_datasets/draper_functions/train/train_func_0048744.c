registerScrollingManager(QGraphicsWidget *widget)
{
    if (!d->scrollingManagers.contains(widget)) {
        KineticScrolling *scroll = new KineticScrolling(widget);
        d->scrollingManagers.insert(widget, scroll);
        connect(scroll,
                SIGNAL(stateChanged(QAbstractAnimation::State,QAbstractAnimation::State)), this,
                SLOT(scrollStateChanged(QAbstractAnimation::State,QAbstractAnimation::State)));
    }
}
