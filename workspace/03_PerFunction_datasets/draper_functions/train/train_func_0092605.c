qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GamesListModel *_t = static_cast<GamesListModel *>(_o);
        switch (_id) {
        case 0: _t->CloseEditorSignal((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->SaveListGameSignal((*reinterpret_cast< CCGame*(*)>(_a[1]))); break;
        case 2: _t->NewGameInputSignal((*reinterpret_cast< CCGame*(*)>(_a[1]))); break;
        case 3: _t->ValidNameCommitSignal(); break;
        case 4: _t->HoverRowSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}
