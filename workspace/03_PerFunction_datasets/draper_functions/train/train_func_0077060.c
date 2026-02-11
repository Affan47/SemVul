qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Clock *_t = static_cast<Clock *>(_o);
        switch (_id) {
        case 0: _t->togglePaused(); break;
        case 1: _t->start(); break;
        case 2: _t->stop(); break;
        case 3: _t->setLoading(); break;
        case 4: _t->setPaused((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->tick(); break;
        default: ;
        }
    }
}
