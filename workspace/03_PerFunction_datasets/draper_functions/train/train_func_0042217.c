qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ColourPicker *_t = static_cast<ColourPicker *>(_o);
        switch (_id) {
        case 0: _t->setColour((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 1: _t->colourChosen((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 2: _t->moreColours(); break;
        case 3: _t->doShowPopup(); break;
        default: ;
        }
    }
}
