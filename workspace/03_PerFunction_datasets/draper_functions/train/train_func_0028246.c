qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ScrobblerHttp *_t = static_cast<ScrobblerHttp *>(_o);
        switch (_id) {
        case 0: _t->done((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onRequestFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->request(); break;
        default: ;
        }
    }
}
