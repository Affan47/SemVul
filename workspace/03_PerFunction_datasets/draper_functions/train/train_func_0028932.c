qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CodeEdit *_t = static_cast<CodeEdit *>(_o);
        switch (_id) {
        case 0: _t->acceptDialog(); break;
        case 1: _t->insertCompletion((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->updateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->highlightCurrentLine(); break;
        case 4: _t->updateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}
