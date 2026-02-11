qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GcCalendar *_t = static_cast<GcCalendar *>(_o);
        switch (_id) {
        case 0: _t->dateRangeChanged((*reinterpret_cast< DateRange(*)>(_a[1]))); break;
        case 1: _t->setRide((*reinterpret_cast< RideItem*(*)>(_a[1]))); break;
        case 2: _t->refresh(); break;
        case 3: _t->setSummary(); break;
        case 4: _t->setFilter((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 5: _t->clearFilter(); break;
        default: ;
        }
    }
}
