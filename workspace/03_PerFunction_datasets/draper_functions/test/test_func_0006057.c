qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ListingDialog *_t = static_cast<ListingDialog *>(_o);
        switch (_id) {
        case 0: _t->addEntry(); break;
        case 1: _t->modifyEntry((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->deleteEntry((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
