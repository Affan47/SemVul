qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ContextThreadLoop *_t = static_cast<ContextThreadLoop *>(_o);
        switch (_id) {
        case 0: _t->notify((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 1: _t->eval((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 2: _t->eval((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->setContext((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 4: _t->startLoop(); break;
        case 5: { bool _r = _t->stopLoop((*reinterpret_cast< ulong(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->stopLoop();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: _t->sync(); break;
        case 8: { bool _r = _t->running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: _t->name(); break;
        default: ;
        }
    }
}
