qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QwtAnalogClock *_t = static_cast<QwtAnalogClock *>(_o);
        switch (_id) {
        case 0: _t->setCurrentTime(); break;
        case 1: _t->setTime((*reinterpret_cast< const QTime(*)>(_a[1]))); break;
        case 2: _t->setTime(); break;
        default: ;
        }
    }
}
