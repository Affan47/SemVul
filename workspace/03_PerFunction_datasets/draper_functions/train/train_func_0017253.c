qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GLEPropertyEditor *_t = static_cast<GLEPropertyEditor *>(_o);
        switch (_id) {
        case 0: _t->propertiesHaveChanged(); break;
        case 1: _t->objectsSelected((*reinterpret_cast< QList<GLEDrawingObject*>(*)>(_a[1]))); break;
        case 2: _t->propertyChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        default: ;
        }
    }
}
