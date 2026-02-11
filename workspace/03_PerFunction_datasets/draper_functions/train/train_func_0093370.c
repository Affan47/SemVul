qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Tablebase *_t = static_cast<Tablebase *>(_o);
        switch (_id) {
        case 0: _t->bestMove((*reinterpret_cast< Move(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->getBestMove((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->abortLookup(); break;
        default: ;
        }
    }
}
