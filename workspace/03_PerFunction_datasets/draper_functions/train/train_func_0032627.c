speed(KJob *job, unsigned long value)
{
    if (!d->progressJobView.contains(job)) {
        return;
    }

    org::kde::JobViewV2 *jobView = d->progressJobView[job];

    jobView->setSpeed(value);
}
