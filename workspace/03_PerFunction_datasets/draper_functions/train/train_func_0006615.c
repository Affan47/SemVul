qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FileTransferHandler *_t = static_cast<FileTransferHandler *>(_o);
        switch (_id) {
        case 0: _t->accepted(); break;
        case 1: _t->statusMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->connected(); break;
        case 3: _t->progress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qlonglong(*)>(_a[2]))); break;
        case 4: _t->error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 5: _t->s5b_proxyQuery(); break;
        case 6: _t->s5b_proxyResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->s5b_requesting(); break;
        case 8: _t->s5b_accepted(); break;
        case 9: _t->s5b_tryingHosts((*reinterpret_cast< const StreamHostList(*)>(_a[1]))); break;
        case 10: _t->s5b_proxyConnect(); break;
        case 11: _t->s5b_waitingForActivation(); break;
        case 12: _t->ft_accepted(); break;
        case 13: _t->ft_connected(); break;
        case 14: _t->ft_readyRead((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 15: _t->ft_bytesWritten((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->ft_error((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->trySend(); break;
        case 18: _t->doFinish(); break;
        default: ;
        }
    }
}
