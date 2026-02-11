qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Task *_t = static_cast<Task *>(_o);
        switch (_id) {
        case 0: _t->mouseMotion((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->mouseWheel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->mouseButtonPressed((*reinterpret_cast< ActionTools::SystemInput::Button(*)>(_a[1]))); break;
        case 3: _t->mouseButtonReleased((*reinterpret_cast< ActionTools::SystemInput::Button(*)>(_a[1]))); break;
        case 4: _t->keyPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->keyReleased((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->start(); break;
        case 7: _t->stop(); break;
        case 8: _t->processReplies(); break;
        default: ;
        }
    }
}
