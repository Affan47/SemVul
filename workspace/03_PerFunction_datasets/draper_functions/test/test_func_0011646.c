qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GenericUtility *_t = static_cast<GenericUtility *>(_o);
        switch (_id) {
        case 0: _t->error(); break;
        case 1: _t->output((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->timeout(); break;
        case 3: _t->finished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 4: _t->errorSlot(); break;
        case 5: _t->runnerError((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}
