qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UserModel *_t = static_cast<UserModel *>(_o);
        switch (_id) {
        case 0: _t->userAboutToConnect((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->userConnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->userAboutToDisconnect((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->userDisconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->userDocumentsChanged(); break;
        case 5: { bool _r = _t->submitAll();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->submitUser((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->submitRow((*reinterpret_cast< const int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->revertAll();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: _t->updateUserPreferences(); break;
        case 10: _t->onCoreDatabaseServerChanged(); break;
        default: ;
        }
    }
}
