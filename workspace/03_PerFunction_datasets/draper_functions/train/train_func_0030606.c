qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        fileManagerView *_t = static_cast<fileManagerView *>(_o);
        switch (_id) {
        case 0: _t->setDir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->fmCreateDirectory(); break;
        case 2: _t->fmRenameFile(); break;
        case 3: _t->fmDeleteFile(); break;
        case 4: _t->fmRefreshFileItem(); break;
        case 5: _t->fmTransferSelectedFiles((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: { int _r = _t->fmUploadFileList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QList<FileInfos>*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: _t->upOneLevelClick(); break;
        case 8: _t->refreshClick(); break;
        case 9: _t->createDirectoryClick(); break;
        case 10: _t->propertiesClick(); break;
        case 11: _t->renameClick(); break;
        case 12: _t->deleteClick(); break;
        default: ;
        }
    }
}
