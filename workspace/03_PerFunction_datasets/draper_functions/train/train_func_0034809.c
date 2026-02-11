qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QObjectArray *_t = static_cast<QObjectArray *>(_o);
        switch (_id) {
        case 0: _t->pushback((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 1: _t->popfront(); break;
        case 2: { QObject* _r = _t->front();
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = _r; }  break;
        case 3: { QObject* _r = _t->back();
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = _r; }  break;
        case 4: { QObject* _r = _t->at((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = _r; }  break;
        case 5: _t->remove((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->insert((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2]))); break;
        case 7: _t->clear(); break;
        default: ;
        }
    }
}
