data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_cookies.size())
        return QVariant();

    switch (role) {
    case CookieModel::SortRole:
    {
        QNetworkCookie cookie = m_cookies.at(index.row());
        switch (index.column()) {
        case 0:
            return cookie.domain();
        case 1:
            return cookie.name();
        case 2:
            return cookie.path();
        case 3:
            return cookie.isSecure();
        case 4:
            return cookie.expirationDate();
        case 5:
            return cookie.value();
        }
    }
    case Qt::DisplayRole:
    case Qt::EditRole: {
        QNetworkCookie cookie = m_cookies.at(index.row());
        switch (index.column()) {
        case 0:
            return cookie.domain();
        case 1:
            return cookie.name();
        case 2:
            return cookie.path();
        case 3:
            return cookie.isSecure() ? tr("true") : tr("false");
        case 4:
            return cookie.isSessionCookie() ? tr("Session cookie") : cookie.expirationDate().toString();
        case 5:
            return cookie.value();
        }
    }
    case Qt::FontRole: {
        QFont font;
        font.setPointSize(10);
        return font;
    }
    }

    return QVariant();
}
