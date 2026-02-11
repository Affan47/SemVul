qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AdvancedSettingsPage *_t = static_cast<AdvancedSettingsPage *>(_o);
        switch (_id) {
        case 0: _t->on_sliderDepth_valueChanged(); break;
        case 1: _t->on_sliderDetail_valueChanged(); break;
        case 2: _t->on_radioAANone_clicked(); break;
        case 3: _t->on_radioAALow_clicked(); break;
        case 4: _t->on_radioAAMedium_clicked(); break;
        case 5: _t->on_radioAAHigh_clicked(); break;
        case 6: _t->on_radioResLow_clicked(); break;
        case 7: _t->on_radioResMedium_clicked(); break;
        case 8: _t->on_radioResHigh_clicked(); break;
        case 9: _t->on_radioResVHigh_clicked(); break;
        case 10: _t->on_sliderHeight_valueChanged(); break;
        case 11: _t->on_sliderZoom_valueChanged(); break;
        case 12: _t->on_buttonRestore_clicked(); break;
        case 13: _t->on_buttonStore_clicked(); break;
        case 14: _t->generatorSettingsChanged(); break;
        case 15: _t->viewSettingsChanged(); break;
        case 16: _t->viewModeChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}
