isShareNameAvailable(const QString &name) const
{
    Q_D(const KSambaShare);
    return d->isShareNameValid(name) && d->isShareNameAvailable(name);
}
