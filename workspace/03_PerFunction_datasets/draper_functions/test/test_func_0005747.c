percent(KJob *job, unsigned long percent)
{
    if (!d->progressWidget.contains(job)) {
        return;
    }

    d->progressWidget[job]->percent(percent);
}
