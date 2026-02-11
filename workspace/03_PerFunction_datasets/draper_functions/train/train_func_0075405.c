compileInterval(int32_t InitOp,  int32_t LoopOp)
{


    int32_t   topOfBlock = blockTopLoc(TRUE);
    insertOp(topOfBlock);
    insertOp(topOfBlock);
    insertOp(topOfBlock);


    int32_t   dataSize = fIntervalUpper < 0 ? 2 : 1;
    int32_t   counterLoc = allocateStackData(dataSize);

    int32_t   op = buildOp(InitOp, counterLoc);
    fRXPat->fCompiledPat->setElementAt(op, topOfBlock);


    int32_t loopEnd = fRXPat->fCompiledPat->size();
    op = buildOp(URX_RELOC_OPRND, loopEnd);
    fRXPat->fCompiledPat->setElementAt(op, topOfBlock+1);


    fRXPat->fCompiledPat->setElementAt(fIntervalLow, topOfBlock+2);
    fRXPat->fCompiledPat->setElementAt(fIntervalUpper, topOfBlock+3);


    appendOp(LoopOp, topOfBlock);

    if ((fIntervalLow & 0xff000000) != 0 ||
        (fIntervalUpper > 0 && (fIntervalUpper & 0xff000000) != 0)) {
            error(U_REGEX_NUMBER_TOO_BIG);
        }

    if (fIntervalLow > fIntervalUpper && fIntervalUpper != -1) {
        error(U_REGEX_MAX_LT_MIN);
    }
}
