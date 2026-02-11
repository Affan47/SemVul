qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GroupDefinition *_t = static_cast<GroupDefinition *>(_o);
        switch (_id) {
        case 0: _t->masterEditorBuilt(); break;
        case 1: _t->masterTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->masterCodeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}
