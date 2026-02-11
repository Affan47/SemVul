infoMessage(KJob *job, const QString &plain, const QString &rich)
{
    Q_UNUSED(rich)

    if (!d->progressJobView.contains(job)) {
        return;
    }

    org::kde::JobViewV2 *jobView = d->progressJobView[job];

    jobView->setInfoMessage(plain);
}
