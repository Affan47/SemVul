qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Graphics *_t = static_cast<Graphics *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->cloneable();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { QVariant _r = _t->create((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantMap(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 2: { QVariant _r = _t->create((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}
