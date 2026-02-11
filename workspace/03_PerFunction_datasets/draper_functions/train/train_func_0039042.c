qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        myTopLevel *_t = static_cast<myTopLevel *>(_o);
        switch (_id) {
        case 0: _t->slot_help(); break;
        case 1: _t->slot_about(); break;
        case 2: _t->slot_new_game(); break;
        case 3: _t->slot_open_game(); break;
        case 4: _t->slot_save_game(); break;
        case 5: _t->slot_next_round(); break;
        case 6: _t->slot_notation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->slot_notation_font(); break;
        case 8: _t->slot_working((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->set_theme((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 10: _t->warning((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
