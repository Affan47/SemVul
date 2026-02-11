cookiesForUrl(const QUrl &url) const
{
    QList<QNetworkCookie> cookieList;

    if (!d->isEnabled) {
        return cookieList;
    }
    QDBusInterface kcookiejar("org.kde.kded", "/modules/kcookiejar", "org.kde.KCookieServer");
    QDBusReply<QString> reply = kcookiejar.call("findDOMCookies", url.toString(QUrl::RemoveUserInfo), (qlonglong)d->windowId);

    if (!reply.isValid()) {
        kWarning(7044) << "Unable to communicate with the cookiejar!";
        return cookieList;
    }

    const QString cookieStr = reply.value();
    const QStringList cookies = cookieStr.split(QL1S("; "), QString::SkipEmptyParts);
    Q_FOREACH(const QString& cookie, cookies) {
        const int index = cookie.indexOf(QL1C('='));
        const QString name = cookie.left(index);
        const QString value = cookie.right((cookie.length() - index - 1));
        cookieList << QNetworkCookie(name.toUtf8(), value.toUtf8());

    }

    return cookieList;
}
