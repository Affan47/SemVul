qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GroupsForm *_t = static_cast<GroupsForm *>(_o);
        switch (_id) {
        case 0: _t->addGroup(); break;
        case 1: _t->removeGroup(); break;
        case 2: _t->modifyGroup(); break;
        case 3: _t->sortGroups(); break;
        case 4: _t->yearChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->groupChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->activateStudents(); break;
        case 7: _t->deactivateStudents(); break;
        default: ;
        }
    }
}
