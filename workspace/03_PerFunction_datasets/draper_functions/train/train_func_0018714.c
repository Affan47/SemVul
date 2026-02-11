removeOffscreenWidget(QGraphicsWidget *widget)
{
    QMutableHashIterator<uint, QGraphicsWidget *> it(d->offscreenWidgets);

    while (it.hasNext()) {
        if (it.next().value() == widget) {
            it.remove();
            return;
        }
    }
}
