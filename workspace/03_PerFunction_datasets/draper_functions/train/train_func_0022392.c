qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ModifyConstraintActivityPreferredStartingTimesForm *_t = static_cast<ModifyConstraintActivityPreferredStartingTimesForm *>(_o);
        switch (_id) {
        case 0: _t->filterChanged(); break;
        case 1: _t->ok(); break;
        case 2: _t->cancel(); break;
        case 3: _t->itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->horizontalHeaderClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->verticalHeaderClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->setAllSlotsAllowed(); break;
        case 7: _t->setAllSlotsNotAllowed(); break;
        default: ;
        }
    }
}
