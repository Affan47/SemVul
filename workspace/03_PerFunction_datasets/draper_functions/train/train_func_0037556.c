unregisterJob(KJob *job)
{
    KAbstractWidgetJobTracker::unregisterJob(job);

    d->progressWidgetsToBeShown.removeAll(job);
    KWidgetJobTracker::Private::ProgressWidget *pWidget = d->progressWidget.value(job, 0);
    if (!pWidget) {
        return;
    }

    pWidget->jobRegistered = false;
    pWidget->deref();
}
