qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CategoryLabelsModel *_t = static_cast<CategoryLabelsModel *>(_o);
        switch (_id) {
        case 0: _t->labelChanged((*reinterpret_cast< const Category::CategoryItem*(*)>(_a[1]))); break;
        case 1: { bool _r = _t->submit();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}
