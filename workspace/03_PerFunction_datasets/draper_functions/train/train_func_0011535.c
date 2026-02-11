qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QwtPicker *_t = static_cast<QwtPicker *>(_o);
        switch (_id) {
        case 0: _t->activated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->selected((*reinterpret_cast< const QPolygon(*)>(_a[1]))); break;
        case 2: _t->appended((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 3: _t->moved((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->removed((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 5: _t->changed((*reinterpret_cast< const QPolygon(*)>(_a[1]))); break;
        case 6: _t->setEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}
