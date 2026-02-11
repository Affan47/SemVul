qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtAbstractSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;

#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< KnobStyle*>(_v) = knobStyle(); break;
        case 1: *reinterpret_cast< MarkerStyle*>(_v) = markerStyle(); break;
        case 2: *reinterpret_cast< int*>(_v) = knobWidth(); break;
        case 3: *reinterpret_cast< int*>(_v) = borderWidth(); break;
        case 4: *reinterpret_cast< double*>(_v) = totalAngle(); break;
        case 5: *reinterpret_cast< int*>(_v) = markerSize(); break;
        case 6: *reinterpret_cast< int*>(_v) = borderWidth(); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setKnobStyle(*reinterpret_cast< KnobStyle*>(_v)); break;
        case 1: setMarkerStyle(*reinterpret_cast< MarkerStyle*>(_v)); break;
        case 2: setKnobWidth(*reinterpret_cast< int*>(_v)); break;
        case 3: setBorderWidth(*reinterpret_cast< int*>(_v)); break;
        case 4: setTotalAngle(*reinterpret_cast< double*>(_v)); break;
        case 5: setMarkerSize(*reinterpret_cast< int*>(_v)); break;
        case 6: setBorderWidth(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif
    return _id;
}
