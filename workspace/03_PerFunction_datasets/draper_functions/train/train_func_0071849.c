qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PmhCategoryModel *_t = static_cast<PmhCategoryModel *>(_o);
        switch (_id) {
        case 0: _t->onCurrentPatientChanged(); break;
        case 1: _t->updateCategoryLabel((*reinterpret_cast< const Category::CategoryItem*(*)>(_a[1]))); break;
        case 2: _t->retranslate(); break;
        default: ;
        }
    }
}
