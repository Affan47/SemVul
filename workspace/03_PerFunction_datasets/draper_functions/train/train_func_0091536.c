qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DirectoryView *_t = static_cast<DirectoryView *>(_o);
        switch (_id) {
        case 0: _t->setDir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->fvUpOneLevel(); break;
        case 2: _t->fvCreateDirectory(); break;
        case 3: _t->fvRenameFile(); break;
        case 4: _t->fvDeleteFile(); break;
        case 5: _t->fvProperties(); break;
        case 6: _t->fvRefreshFileItem(); break;
        case 7: _t->fvTransferSelectedFiles((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setItemExpanded((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->openFolder(); break;
        case 10: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 11: _t->fvItemRenamed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}
