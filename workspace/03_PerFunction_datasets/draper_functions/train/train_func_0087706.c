qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ComprovaFigures *_t = static_cast<ComprovaFigures *>(_o);
        switch (_id) {
        case 0: _t->seleccioFiguraJoc(); break;
        case 1: _t->seleccioFiguraNova(); break;
        case 2: { QString _r = _t->seleccioFigura((*reinterpret_cast< QTreeWidget*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: _t->obreFiguresGeneradesSlot(); break;
        case 4: _t->comparaFiguresProgramaSlot(); break;
        case 5: _t->figuraSeguentSlot(); break;
        case 6: _t->figuraAnteriorSlot(); break;
        case 7: _t->eliminaFiguraSlot(); break;
        case 8: _t->desaCanvisSlot(); break;
        case 9: _t->canviaNumeracioFiguresGeneradesSlot(); break;
        case 10: _t->comparaFiguresGeneradesSlot(); break;
        case 11: _t->activaBotonsMovimentLlistaComparacioFigures(); break;
        case 12: _t->desaDadesCercaFigures(); break;
        case 13: _t->tancaSlot(); break;
        case 14: _t->desaLlistaComparacioSlot(); break;
        default: ;
        }
    }
}
