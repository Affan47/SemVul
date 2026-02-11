qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SplitActivityWizard *_t = static_cast<SplitActivityWizard *>(_o);
        switch (_id) {
        case 0: { QString _r = _t->hasBackup((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QStringList _r = _t->conflicts((*reinterpret_cast< QDateTime(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 2: _t->setIntervalsList((*reinterpret_cast< SplitSelect*(*)>(_a[1]))); break;
        case 3: _t->setFilesList(); break;
        default: ;
        }
    }
}
