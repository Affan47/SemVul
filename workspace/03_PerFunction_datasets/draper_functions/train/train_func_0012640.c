canRequest(const KUrl& url) const
{
    if (isUnique())
        return false;

    WTF::RefPtr<SecurityOrigin> targetOrigin = SecurityOrigin::create(url);
    if (targetOrigin->isUnique())
        return false;


    if (isSameSchemeHostPort(targetOrigin.get()))
        return true;

    return false;
}
