qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NetworkDiskCache *_t = static_cast<NetworkDiskCache *>(_o);
        switch (_id) {
        case 0: _t->privacyChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}
