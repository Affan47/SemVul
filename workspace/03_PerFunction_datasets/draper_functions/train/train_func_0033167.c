isReleaseCandidate()
{
    return qApp->applicationVersion().contains("rc", Qt::CaseInsensitive);
}
