qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UpdateDialog *_t = static_cast<UpdateDialog *>(_o);
        switch (_id) {
        case 0: _t->enableAgainSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->releasesAvailableSlot(); break;
        case 2: _t->xmlErrorSlot((*reinterpret_cast< QXmlStreamReader::Error(*)>(_a[1]))); break;
        case 3: _t->httpErrorSlot((*reinterpret_cast< QHttp::Error(*)>(_a[1]))); break;
        case 4: _t->stopClose(); break;
        default: ;
        }
    }
}
