qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CUpdateInfoGetter *_t = static_cast<CUpdateInfoGetter *>(_o);
        switch (_id) {
        case 0: _t->updateInfoDone((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->progressMade((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->statusChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->downloadFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->statusChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sendProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->readyRead((*reinterpret_cast< const QHttpResponseHeader(*)>(_a[1]))); break;
        case 7: _t->requestStarted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->responseHeaderReceived((*reinterpret_cast< const QHttpResponseHeader(*)>(_a[1]))); break;
        default: ;
        }
    }
}
