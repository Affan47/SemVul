updateTimeFromComboSelection(const int index)
{
    if (index == -1) {
        setTime(QTime(0,0));
        return;
    }

    QTime time = d->combo->itemData(index).toTime();
    setTime(time);
}
