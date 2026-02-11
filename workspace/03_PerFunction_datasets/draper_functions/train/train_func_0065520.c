qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ExitTunnel *_t = static_cast<ExitTunnel *>(_o);
        switch (_id) {
        case 0: _t->Stopped(); break;
        case 1: _t->Stop(); break;
        case 2: _t->SessionData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->DiscardProxy(); break;
        case 4: _t->TcpProxyStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 5: _t->TcpReadFromProxy(); break;
        case 6: _t->UdpReadFromProxy(); break;
        case 7: _t->TcpDnsLookupFinished((*reinterpret_cast< const QHostInfo(*)>(_a[1]))); break;
        case 8: _t->UdpDnsLookupFinished((*reinterpret_cast< const QHostInfo(*)>(_a[1]))); break;
        case 9: _t->HandleError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 10: _t->UdpTimeout(); break;
        default: ;
        }
    }
}
