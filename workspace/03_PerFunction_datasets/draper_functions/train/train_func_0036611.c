qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = currentTitle(); break;
        case 1: *reinterpret_cast< QString*>(_v) = currentUsualName(); break;
        case 2: *reinterpret_cast< QString*>(_v) = currentOtherNames(); break;
        case 3: *reinterpret_cast< QString*>(_v) = currentFirstName(); break;
        case 4: *reinterpret_cast< QDate*>(_v) = currentDateOfBirth(); break;
        case 5: *reinterpret_cast< QString*>(_v) = currentGender(); break;
        case 6: *reinterpret_cast< int*>(_v) = currentGenderIndex(); break;
        case 7: *reinterpret_cast< QString*>(_v) = currentLanguage(); break;
        case 8: *reinterpret_cast< QString*>(_v) = currentClearLogin(); break;
        case 9: *reinterpret_cast< QString*>(_v) = currentClearPassword(); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 10;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif
    return _id;
}
