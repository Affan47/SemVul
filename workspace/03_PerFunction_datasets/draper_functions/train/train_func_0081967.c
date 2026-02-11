qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IcdWidgetManager *_t = static_cast<IcdWidgetManager *>(_o);
        switch (_id) {
        case 0: _t->updateContext((*reinterpret_cast< Core::IContext*(*)>(_a[1])),(*reinterpret_cast< const Core::Context(*)>(_a[2]))); break;
        default: ;
        }
    }
}
