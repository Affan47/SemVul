qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Aerolab *_t = static_cast<Aerolab *>(_o);
        switch (_id) {
        case 0: _t->setAutoEoffset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setConstantAlt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setByDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->configChanged(); break;
        case 4: _t->pointHover((*reinterpret_cast< QwtPlotCurve*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}
