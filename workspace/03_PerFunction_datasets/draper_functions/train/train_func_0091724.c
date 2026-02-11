qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AccountManageDlg *_t = static_cast<AccountManageDlg *>(_o);
        switch (_id) {
        case 0: _t->qlv_selectionChanged((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 1: _t->add(); break;
        case 2: _t->modify(); break;
        case 3: _t->modify((*reinterpret_cast< Q3ListViewItem*(*)>(_a[1]))); break;
        case 4: _t->remove(); break;
        case 5: _t->accountAdded((*reinterpret_cast< PsiAccount*(*)>(_a[1]))); break;
        case 6: _t->accountUpdated((*reinterpret_cast< PsiAccount*(*)>(_a[1]))); break;
        case 7: _t->accountRemoved((*reinterpret_cast< PsiAccount*(*)>(_a[1]))); break;
        default: ;
        }
    }
}
