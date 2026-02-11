setThinFrame(bool set)
{
    if (d->showThinFrame == set) {
        return;
    }
    d->showThinFrame = set;
    d->backgroundPixmap = QPixmap();
}
