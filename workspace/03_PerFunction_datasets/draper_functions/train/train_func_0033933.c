qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NetworkAccessManager *_t = static_cast<NetworkAccessManager *>(_o);
        switch (_id) {
        case 0: _t->requestCreated((*reinterpret_cast< QNetworkAccessManager::Operation(*)>(_a[1])),(*reinterpret_cast< const QNetworkRequest(*)>(_a[2])),(*reinterpret_cast< QNetworkReply*(*)>(_a[3]))); break;
        case 1: _t->loadSettings(); break;
        case 2: _t->authenticationRequired((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 3: _t->proxyAuthenticationRequired((*reinterpret_cast< const QNetworkProxy(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 4: _t->sslErrors((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< const QList<QSslError>(*)>(_a[2]))); break;
        case 5: _t->privacyChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}
