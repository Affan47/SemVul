qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        OptionsTabAppearanceGeneral *_t = static_cast<OptionsTabAppearanceGeneral *>(_o);
        switch (_id) {
        case 0: _t->setData((*reinterpret_cast< PsiCon*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        case 1: _t->chooseColor((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 2: _t->chooseFont((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        default: ;
        }
    }
}
