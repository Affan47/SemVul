qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LogData *_t = static_cast<LogData *>(_o);
        switch (_id) {
        case 0: _t->loadingProgressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->loadingFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->fileChanged((*reinterpret_cast< LogData::MonitoredFileStatus(*)>(_a[1]))); break;
        case 3: _t->fileChangedOnDisk(); break;
        case 4: _t->indexingFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}
