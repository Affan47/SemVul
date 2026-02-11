qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModelBase *_t = static_cast<ModelBase *>(_o);
        switch (_id) {
        case 0: _t->loadedViews((*reinterpret_cast< ModelBase*(*)>(_a[1])),(*reinterpret_cast< QDomElement(*)>(_a[2]))); break;
        case 1: _t->loadedRoot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< ModelBase*(*)>(_a[2])),(*reinterpret_cast< QDomElement(*)>(_a[3]))); break;
        case 2: _t->loadingInstances((*reinterpret_cast< ModelBase*(*)>(_a[1])),(*reinterpret_cast< QDomElement(*)>(_a[2]))); break;
        case 3: _t->loadingInstance((*reinterpret_cast< ModelBase*(*)>(_a[1])),(*reinterpret_cast< QDomElement(*)>(_a[2]))); break;
        case 4: _t->loadedInstances((*reinterpret_cast< ModelBase*(*)>(_a[1])),(*reinterpret_cast< QDomElement(*)>(_a[2]))); break;
        case 5: _t->obsoleteSMDOrientationSignal(); break;
        default: ;
        }
    }
}
