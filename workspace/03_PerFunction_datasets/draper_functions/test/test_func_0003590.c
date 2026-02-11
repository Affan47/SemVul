qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LastFmSettings *_t = static_cast<LastFmSettings *>(_o);
        switch (_id) {
        case 0: _t->userSettingsChanged((*reinterpret_cast< LastFmUserSettings(*)>(_a[1]))); break;
        case 1: _t->appearanceSettingsChanged(); break;
        case 2: _t->userSwitched((*reinterpret_cast< LastFmUserSettings(*)>(_a[1]))); break;
        case 3: _t->userChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
