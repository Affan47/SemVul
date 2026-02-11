saveCookies(const QString &_filename)
{
    KSaveFile cookieFile(_filename);

    if (!cookieFile.open())
       return false;
    cookieFile.setPermissions(QFile::ReadUser|QFile::WriteUser);

    QTextStream ts(&cookieFile);

    ts << "# KDE Cookie File v2\n#\n";

    QString s;
    s.sprintf("%-20s %-20s %-12s %-10s %-4s %-20s %-4s %s\n",
              "# Host", "Domain", "Path", "Exp.date", "Prot",
              "Name", "Sec", "Value");
    ts << s.toLatin1().constData();

    QStringListIterator it(m_domainList);
    while (it.hasNext())
    {
        const QString& domain = it.next();
        bool domainPrinted = false;

        KHttpCookieList *cookieList = m_cookieDomains.value(domain);
        if (!cookieList)
            continue;

        QMutableListIterator<KHttpCookie> cookieIterator(*cookieList);
        while (cookieIterator.hasNext()) {
            const KHttpCookie& cookie = cookieIterator.next();

            if (cookie.isExpired()) {

                cookieIterator.remove();
                continue;
            }
            if (cookieIsPersistent(cookie)) {

                if (!domainPrinted) {
                    domainPrinted = true;
                    ts << '[' << domain.toLocal8Bit().data() << "]\n";
                }

                const QString path = QL1S("\"") + cookie.path() + QL1C('"');
                const QString domain = QL1S("\"") + cookie.domain() + QL1C('"');
                const QString host = hostWithPort(&cookie);


                s.sprintf("%-20s %-20s %-12s %10lld  %3d %-20s %-4i %s\n",
                        host.toLatin1().constData(), domain.toLatin1().constData(),
                        path.toLatin1().constData(), cookie.expireDate(),
                        cookie.protocolVersion(),
                        cookie.name().isEmpty() ? cookie.value().toLatin1().constData() : cookie.name().toLatin1().constData(),
                        (cookie.isSecure() ? 1 : 0) + (cookie.isHttpOnly() ? 2 : 0) +
                        (cookie.hasExplicitPath() ? 4 : 0) + (cookie.name().isEmpty() ? 8 : 0),
                        cookie.value().toLatin1().constData());
                ts << s.toLatin1().constData();
            }
        }
    }

    return cookieFile.finalize();
}
