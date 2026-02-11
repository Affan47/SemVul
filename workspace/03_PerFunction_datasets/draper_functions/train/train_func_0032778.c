qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TimerManager *_t = static_cast<TimerManager *>(_o);
        switch (_id) {
        case 0: _t->saveTimers(); break;
        case 1: _t->newTimer(); break;
        case 2: _t->recentTimer((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 3: _t->recentTimerMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 4: _t->timerChanged((*reinterpret_cast< Timer*(*)>(_a[1]))); break;
        case 5: _t->timerDeleted((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 6: _t->timerEdited((*reinterpret_cast< Timer*(*)>(_a[1]))); break;
        case 7: _t->toggleVisibility(); break;
        case 8: _t->updateClock(); break;
        default: ;
        }
    }
}
