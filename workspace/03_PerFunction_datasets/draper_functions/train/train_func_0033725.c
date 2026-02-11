cookieMatches(const KHttpCookie& c,
                                  const QString &domain, const QString &fqdn,
                                  const QString &path, const QString &name)
{
    const bool hasDomain = !domain.isEmpty();
    return (((hasDomain && c.domain() == domain) || fqdn == c.host()) &&
            (c.path() == path) && (c.name() == name) &&
            (!c.isExpired()));
}
