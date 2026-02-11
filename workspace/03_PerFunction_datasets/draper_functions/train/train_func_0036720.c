qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ShareDialog *_t = static_cast<ShareDialog *>(_o);
        switch (_id) {
        case 0: _t->onRecipientChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onUserChanged((*reinterpret_cast< LastFmUserSettings(*)>(_a[1]))); break;
        case 2: _t->onFriendsReturn((*reinterpret_cast< Request*(*)>(_a[1]))); break;
        default: ;
        }
    }
}
