qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SubgroupsForm *_t = static_cast<SubgroupsForm *>(_o);
        switch (_id) {
        case 0: _t->addSubgroup(); break;
        case 1: _t->removeSubgroup(); break;
        case 2: _t->modifySubgroup(); break;
        case 3: _t->sortSubgroups(); break;
        case 4: _t->yearChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->groupChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->subgroupChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->activateStudents(); break;
        case 8: _t->deactivateStudents(); break;
        default: ;
        }
    }
}
