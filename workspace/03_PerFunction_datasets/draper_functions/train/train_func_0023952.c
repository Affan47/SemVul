qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ToolsRhoEstimator *_t = static_cast<ToolsRhoEstimator *>(_o);
        switch (_id) {
        case 0: _t->on_radio_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_btnOK_clicked(); break;
        case 2: _t->on_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}
