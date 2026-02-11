qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BankAccountsWidget *_t = static_cast<BankAccountsWidget *>(_o);
        switch (_id) {
        case 0: _t->Account_Changed((*reinterpret_cast< const aqb_AccountInfo*(*)>(_a[1]))); break;
        case 1: _t->setSelectedAccount((*reinterpret_cast< const aqb_AccountInfo*(*)>(_a[1]))); break;
        case 2: _t->accountChangedUpdateDisplay((*reinterpret_cast< const aqb_AccountInfo*(*)>(_a[1]))); break;
        case 3: _t->setAccounts((*reinterpret_cast< const aqb_Accounts*(*)>(_a[1]))); break;
        case 4: _t->on_treeWidget_itemSelectionChanged(); break;
        default: ;
        }
    }
}
