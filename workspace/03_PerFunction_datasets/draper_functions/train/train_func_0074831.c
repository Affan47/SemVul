qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LTMTool *_t = static_cast<LTMTool *>(_o);
        switch (_id) {
        case 0: _t->filterChanged(); break;
        case 1: _t->metricSelected(); break;
        case 2: _t->useCustomRange((*reinterpret_cast< DateRange(*)>(_a[1]))); break;
        case 3: _t->useStandardRange(); break;
        case 4: _t->useThruToday(); break;
        case 5: _t->metricTreeWidgetSelectionChanged(); break;
        case 6: _t->metricTreePopup((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 7: _t->colorPicker(); break;
        case 8: _t->editMetric(); break;
        case 9: _t->configChanged(); break;
        case 10: _t->clearFilter(); break;
        case 11: _t->setFilter((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        default: ;
        }
    }
}
