percent(KJob *job, unsigned long percent)
{
    if (!d->progressJobView.contains(job)) {
        return;
    }

    org::kde::JobViewV2 *jobView = d->progressJobView[job];

    jobView->setPercent(percent);
}
