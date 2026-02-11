qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HttpMultiDownloader *_t = static_cast<HttpMultiDownloader *>(_o);
        switch (_id) {
        case 0: _t->progressMessageChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->downloadFinished((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 2: _t->downloadProgressPermille((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->allDownloadFinished(); break;
        case 4: { bool _r = _t->startDownload();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->onCurrentDownloadFinished();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}
