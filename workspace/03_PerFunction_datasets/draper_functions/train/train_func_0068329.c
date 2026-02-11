find_comp_unit(U8_T ID) {
    unsigned i;
    CompUnit * Unit;

    for (i = 0; i < sCache->mCompUnitsCnt; i++) {
        Unit = sCache->mCompUnits[i];
        if (Unit->mID == ID) return Unit;
    }
    if (sCache->mCompUnitsCnt >= sCompUnitsMax) {
        sCompUnitsMax = sCompUnitsMax == 0 ? 16 : sCompUnitsMax * 2;
        sCache->mCompUnits = (CompUnit **)loc_realloc(sCache->mCompUnits, sizeof(CompUnit *) * sCompUnitsMax);
    }
    Unit = (CompUnit *)loc_alloc_zero(sizeof(CompUnit));
    Unit->mID = ID;
    sCache->mCompUnits[sCache->mCompUnitsCnt++] = Unit;
    return Unit;
}
