qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProcessingTree *_t = static_cast<ProcessingTree *>(_o);
        switch (_id) {
        case 0: _t->PressProcessing((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->filterProcessings((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
