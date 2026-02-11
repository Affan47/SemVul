qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PrescriptionViewer *_t = static_cast<PrescriptionViewer *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->savePrescription();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->saveAsPrescription();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->clear(); break;
        case 3: _t->removeTriggered(); break;
        case 4: _t->moveUp(); break;
        case 5: _t->moveDown(); break;
        case 6: _t->sortDrugs(); break;
        case 7: _t->showDrugInfo((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->showDosageDialog((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: _t->showDosageDialog(); break;
        case 10: _t->viewInteractions(); break;
        case 11: _t->changeDuration(); break;
        case 12: _t->changeDurationTo(); break;
        case 13: _t->openProtocolPreferencesDialog(); break;
        case 14: _t->copyPrescriptionItem(); break;
        case 15: _t->on_listView_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}
