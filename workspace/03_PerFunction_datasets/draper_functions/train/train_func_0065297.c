qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IBBManager *_t = static_cast<IBBManager *>(_o);
        switch (_id) {
        case 0: _t->incomingReady(); break;
        case 1: _t->ibb_incomingRequest((*reinterpret_cast< const Jid(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QDomElement(*)>(_a[3]))); break;
        case 2: _t->ibb_incomingData((*reinterpret_cast< const Jid(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QByteArray(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        default: ;
        }
    }
}
