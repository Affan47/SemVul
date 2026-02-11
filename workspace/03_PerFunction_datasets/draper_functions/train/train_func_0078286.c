qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AutorouterSettingsDialog *_t = static_cast<AutorouterSettingsDialog *>(_o);
        switch (_id) {
        case 0: _t->production((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->widthEntry((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->changeUnits((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->changeHoleSize((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->changeDiameter(); break;
        case 5: _t->changeThickness(); break;
        case 6: _t->toInches(); break;
        case 7: _t->toMM(); break;
        case 8: _t->keepoutEntry(); break;
        default: ;
        }
    }
}
