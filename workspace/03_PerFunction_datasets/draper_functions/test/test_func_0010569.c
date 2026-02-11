qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PathRequester *_t = static_cast<PathRequester *>(_o);
        switch (_id) {
        case 0: _t->textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->choose(); break;
        default: ;
        }
    }
}
