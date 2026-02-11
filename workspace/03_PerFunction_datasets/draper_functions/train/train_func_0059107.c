qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EventListWidget *_t = static_cast<EventListWidget *>(_o);
        switch (_id) {
        case 0: _t->filterRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->renameRequest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->filterEventPlayerRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->raiseRequest(); break;
        case 4: _t->findEvent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setDatabase((*reinterpret_cast< DatabaseInfo*(*)>(_a[1]))); break;
        case 6: _t->filterSelectedEvent(); break;
        case 7: _t->renameSelectedEvent(); break;
        case 8: _t->slotReconfigure(); break;
        case 9: _t->selectionChangedSlot(); break;
        case 10: _t->slotLinkClicked((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 11: _t->selectEvent((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->eventSelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}
