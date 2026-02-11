qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DrugsModel *_t = static_cast<DrugsModel *>(_o);
        switch (_id) {
        case 0: _t->numberOfRowsChanged(); break;
        case 1: { bool _r = _t->submit();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->resetModel(); break;
        case 3: _t->dosageDatabaseChanged(); break;
        default: ;
        }
    }
}
