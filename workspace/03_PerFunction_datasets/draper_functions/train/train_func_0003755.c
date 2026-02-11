cookieJarWindowid() const
{
    KIO::Integration::CookieJar *jar = qobject_cast<KIO::Integration::CookieJar *> (cookieJar());
    if (jar)
        return jar->windowId();

    return 0;
}
