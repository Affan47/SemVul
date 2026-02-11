qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetWrapper *_t = static_cast<WidgetWrapper *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->setWidget((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->wrap((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->setLayout((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}
