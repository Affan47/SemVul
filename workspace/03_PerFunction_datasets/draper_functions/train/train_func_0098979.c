qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WidgetPlaque *_t = static_cast<WidgetPlaque *>(_o);
        switch (_id) {
        case 0: _t->change((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->valeur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->pbClicked(); break;
        case 3: _t->displayRefresh((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->updateEtat((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->estReglable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->colorise((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->nonCliquable((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 9: _t->mouseReleaseEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 10: _t->wheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}
