qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RealtimePlotWindow *_t = static_cast<RealtimePlotWindow *>(_o);
        switch (_id) {
        case 0: _t->telemetryUpdate((*reinterpret_cast< RealtimeData(*)>(_a[1]))); break;
        case 1: _t->start(); break;
        case 2: _t->stop(); break;
        case 3: _t->pause(); break;
        case 4: _t->setSmoothingFromSlider(); break;
        case 5: _t->setSmoothingFromLineEdit(); break;
        case 6: _t->setShowPower((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setShowPow30s((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setShowHr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setShowSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setShowCad((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setShowAlt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setSmoothing((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}
