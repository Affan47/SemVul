qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CountryComboBox *_t = static_cast<CountryComboBox *>(_o);
        switch (_id) {
        case 0: _t->currentCountryChanged((*reinterpret_cast< QLocale::Country(*)>(_a[1]))); break;
        case 1: _t->currentIsoCountryChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setCurrentIsoCountry((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->setCurrentCountry((*reinterpret_cast< QLocale::Country(*)>(_a[1]))); break;
        case 4: _t->on_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}
