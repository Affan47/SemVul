qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FDockWidget *_t = static_cast<FDockWidget *>(_o);
        switch (_id) {
        case 0: _t->dockChangeActivationSignal((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 1: _t->positionChanged(); break;
        case 2: _t->restoreState(); break;
        default: ;
        }
    }
}
