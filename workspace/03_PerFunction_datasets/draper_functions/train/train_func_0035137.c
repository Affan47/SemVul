qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ActionFactory *_t = static_cast<ActionFactory *>(_o);
        switch (_id) {
        case 0: _t->actionPackLoadError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
