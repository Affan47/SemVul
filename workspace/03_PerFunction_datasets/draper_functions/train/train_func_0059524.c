qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DefinedCommand *_t = static_cast<DefinedCommand *>(_o);
        switch (_id) {
        case 0: _t->executeCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->copyAction(); break;
        case 2: _t->mkDirAction(); break;
        case 3: _t->setAction(); break;
        case 4: _t->delFileAction(); break;
        case 5: _t->delFolderAction(); break;
        case 6: _t->shutdownAction(); break;
        case 7: _t->ipconfigAction(); break;
        case 8: _t->networkStatsAction(); break;
        case 9: _t->pingAction(); break;
        case 10: _t->routeTableAction(); break;
        case 11: _t->executeDefinedCommand((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
