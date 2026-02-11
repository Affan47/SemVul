qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HrPwWindow *_t = static_cast<HrPwWindow *>(_o);
        switch (_id) {
        case 0: _t->rideSelected(); break;
        case 1: _t->setJoinLineFromCheckBox(); break;
        case 2: _t->setDelayFromLineEdit(); break;
        case 3: _t->setDelayFromSlider(); break;
        case 4: _t->setSmoothingFromLineEdit(); break;
        case 5: _t->setSmoothingFromSlider(); break;
        case 6: _t->setrDelayFromLineEdit(); break;
        case 7: _t->setrDelayFromSlider(); break;
        case 8: _t->setrSmoothingFromLineEdit(); break;
        case 9: _t->setrSmoothingFromSlider(); break;
        case 10: _t->setShadeZones(); break;
        case 11: _t->setSmooth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->showHidePlot(); break;
        case 13: _t->setDelay((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}
