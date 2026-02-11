qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AmoraServer *_t = static_cast<AmoraServer *>(_o);
        switch (_id) {
        case 0: _t->clientDisconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->clientConnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onConnection((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onDisconnection((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
