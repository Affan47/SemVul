qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Definitions *_t = static_cast<Definitions *>(_o);
        switch (_id) {
        case 0: _t->clear(); break;
        case 1: _t->addWord((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->solveWord((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->selectWord((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->selectWord(); break;
        case 5: _t->wordSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->wordDefined((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}
