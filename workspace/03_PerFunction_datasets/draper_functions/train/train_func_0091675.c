qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WizardBootstrapPage *_t = static_cast<WizardBootstrapPage *>(_o);
        switch (_id) {
        case 0: _t->infoChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->onTrackFound((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const TrackInfo(*)>(_a[2]))); break;
        case 2: _t->onUploadProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
