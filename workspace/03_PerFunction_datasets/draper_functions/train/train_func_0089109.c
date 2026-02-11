tabLayoutChange()
{
    KTabBar::tabLayoutChange();

    if (shape() != d->shape) {
        d->shape = shape();
        emit shapeChanged(d->shape);
    }
}
