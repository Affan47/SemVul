qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ANTLogger *_t = static_cast<ANTLogger *>(_o);
        switch (_id) {
        case 0: _t->logRawAntMessage((*reinterpret_cast< const ANTMessage(*)>(_a[1])),(*reinterpret_cast< const timeval(*)>(_a[2]))); break;
        case 1: _t->open(); break;
        case 2: _t->close(); break;
        default: ;
        }
    }
}
