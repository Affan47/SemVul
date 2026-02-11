qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QwtPlotZoomer *_t = static_cast<QwtPlotZoomer *>(_o);
        switch (_id) {
        case 0: _t->zoomed((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 1: _t->moveBy((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->moveTo((*reinterpret_cast< const QPointF(*)>(_a[1]))); break;
        case 3: _t->zoom((*reinterpret_cast< const QRectF(*)>(_a[1]))); break;
        case 4: _t->zoom((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}
