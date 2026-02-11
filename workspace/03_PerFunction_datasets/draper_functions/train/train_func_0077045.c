qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SpellChecker *_t = static_cast<SpellChecker *>(_o);
        switch (_id) {
        case 0: _t->reject(); break;
        case 1: _t->suggestionChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->add(); break;
        case 3: _t->ignore(); break;
        case 4: _t->ignoreAll(); break;
        case 5: _t->change(); break;
        case 6: _t->changeAll(); break;
        default: ;
        }
    }
}
