removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid() || !m_cookieJar)
        return false;
    int lastRow = row + count - 1;
    beginRemoveRows(parent, row, lastRow);
    QList<QNetworkCookie> lst = m_cookies;
    for (int i = lastRow; i >= row; --i) {
        lst.removeAt(i);
    }
    disconnect(m_cookieJar, SIGNAL(cookiesChanged()), this, SLOT(cookiesChanged()));
    m_cookieJar->setCookies(lst);
    connect(m_cookieJar, SIGNAL(cookiesChanged()), this, SLOT(cookiesChanged()));

    m_cookies = lst;
    endRemoveRows();
    return true;
}
