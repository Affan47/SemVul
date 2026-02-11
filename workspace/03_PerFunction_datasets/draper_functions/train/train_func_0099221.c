setCurrentActivityId(const QString &id)
{
    if (d->activityId == id) {
        return;
    }

    d->activityId = id;
    emit changed(this);
}
