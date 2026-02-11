qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CheckDirTree *_t = static_cast<CheckDirTree *>(_o);
        switch (_id) {
        case 0: _t->dataChanged(); break;
        case 1: _t->onCollapse((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->onExpand((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->updateNode((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}
