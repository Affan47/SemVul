qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RelayForwarder *_t = static_cast<RelayForwarder *>(_o);
        switch (_id) {
        case 0: _t->IncomingData((*reinterpret_cast< const Request(*)>(_a[1]))); break;
        default: ;
        }
    }
}
