qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MediaInfo *_t = static_cast<MediaInfo *>(_o);
        switch (_id) {
        case 0: _t->pruneVol(); break;
        case 1: _t->purgeVol(); break;
        case 2: _t->deleteVol(); break;
        case 3: _t->editVol(); break;
        case 4: _t->showInfoForJob((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}
