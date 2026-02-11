qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ANTChannel *_t = static_cast<ANTChannel *>(_o);
        switch (_id) {
        case 0: _t->channelInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->dropInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->lostInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->staleInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->searchTimeout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->searchComplete((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}
