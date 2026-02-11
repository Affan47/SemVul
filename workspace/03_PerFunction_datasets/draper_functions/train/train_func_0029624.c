setIgnoredErrors(const QList<KSslError::Error> &errors)
{
    d->ignoredErrors.clear();

    foreach(KSslError::Error e, errors)
        if (!isErrorIgnored(e))
            d->ignoredErrors.append(e);
}
