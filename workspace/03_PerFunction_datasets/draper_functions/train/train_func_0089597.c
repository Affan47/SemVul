exportTable(void *where) {
    RBBIStateTable    *table = (RBBIStateTable *)where;
    uint32_t           state;
    int                col;

    if (U_FAILURE(*fStatus) || fTree == NULL) {
        return;
    }

    if (fRB->fSetBuilder->getNumCharCategories() > 0x7fff ||
        fDStates->size() > 0x7fff) {
        *fStatus = U_BRK_INTERNAL_ERROR;
        return;
    }

    table->fRowLen    = sizeof(RBBIStateTableRow) +
                            sizeof(uint16_t) * (fRB->fSetBuilder->getNumCharCategories() - 2);
    table->fNumStates = fDStates->size();
    table->fFlags     = 0;
    if (fRB->fLookAheadHardBreak) {
        table->fFlags  |= RBBI_LOOKAHEAD_HARD_BREAK;
    }
    if (fRB->fSetBuilder->sawBOF()) {
        table->fFlags  |= RBBI_BOF_REQUIRED;
    }
    table->fReserved  = 0;

    for (state=0; state<table->fNumStates; state++) {
        RBBIStateDescriptor *sd = (RBBIStateDescriptor *)fDStates->elementAt(state);
        RBBIStateTableRow   *row = (RBBIStateTableRow *)(table->fTableData + state*table->fRowLen);
        U_ASSERT (-32768 < sd->fAccepting && sd->fAccepting <= 32767);
        U_ASSERT (-32768 < sd->fLookAhead && sd->fLookAhead <= 32767);
        row->fAccepting = (int16_t)sd->fAccepting;
        row->fLookAhead = (int16_t)sd->fLookAhead;
        row->fTagIdx    = (int16_t)sd->fTagsIdx;
        for (col=0; col<fRB->fSetBuilder->getNumCharCategories(); col++) {
            row->fNextState[col] = (uint16_t)sd->fDtran->elementAti(col);
        }
    }
}
