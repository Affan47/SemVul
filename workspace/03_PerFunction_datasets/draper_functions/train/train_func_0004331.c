qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CodeLineEdit *_t = static_cast<CodeLineEdit *>(_o);
        switch (_id) {
        case 0: _t->codeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->reverseCode(); break;
        case 2: _t->textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->openEditor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->openEditor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->openEditor(); break;
        case 6: _t->showVariableMenuAsPopup(); break;
        case 7: _t->insertVariable((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        default: ;
        }
    }
}
