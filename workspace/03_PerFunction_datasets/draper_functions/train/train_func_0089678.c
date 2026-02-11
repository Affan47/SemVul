qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->setOptions(); break;
        case 1: _t->calculate(); break;
        case 2: _t->copy(); break;
        case 3: _t->new_(); break;
        case 4: _t->load(); break;
        case 5: _t->save(); break;
        case 6: _t->saveAs(); break;
        case 7: _t->help(); break;
        case 8: _t->about(); break;
        case 9: _t->afterCreation(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}
