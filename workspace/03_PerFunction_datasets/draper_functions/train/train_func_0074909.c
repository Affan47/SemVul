qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FormManager *_t = static_cast<FormManager *>(_o);
        switch (_id) {
        case 0: _t->patientFormsLoaded(); break;
        case 1: _t->subFormLoaded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: { bool _r = _t->loadPatientFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->onCurrentPatientChanged();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->insertSubForm((*reinterpret_cast< const SubFormInsertionPoint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->removeSubForm((*reinterpret_cast< const SubFormRemoval(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->readPmhxCategories((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: _t->packChanged((*reinterpret_cast< const DataPack::Pack(*)>(_a[1]))); break;
        default: ;
        }
    }
}
