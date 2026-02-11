generaClase(ushort * bch, uint u, uint clase, uint puestos, uint pos_ini, uint generado) {
        uint ret=0;
        if (clase==puestos) {
            bch[__indiceFunc] = generado;
            __Lis[generado] = __indiceFunc-__indAcumulado;
            __indiceFunc++;
            return 1;
        }
        if (clase<puestos)
            return 0;
        for (uint i=pos_ini;i<u;i++) {
            uint tmp = generado | (1<<i);
            ret += generaClase(bch, u, clase, puestos+1, i+1, tmp);
        }
        return ret;
    }
