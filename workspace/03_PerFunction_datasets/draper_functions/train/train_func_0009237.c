compileInterval(int32_t InitOp,  int32_t LoopOp)
{


    int32_t   topOfBlock = blockTopLoc(TRUE);
    insertOp(topOfBlock);
    insertOp(topOfBlock);
    insertOp(topOfBlock);


    int32_t   counterLoc = fRXPat->fFrameSize;
    fRXPat->fFrameSize++;

    int32_t   op = URX_BUILD(InitOp, counterLoc);
    fRXPat->fCompiledPat->setElementAt(op, topOfBlock);


    int32_t loopEnd = fRXPat->fCompiledPat->size();
    op = URX_BUILD(URX_RELOC_OPRND, loopEnd);
    fRXPat->fCompiledPat->setElementAt(op, topOfBlock+1);


    fRXPat->fCompiledPat->setElementAt(fIntervalLow, topOfBlock+2);
    fRXPat->fCompiledPat->setElementAt(fIntervalUpper, topOfBlock+3);


    op = URX_BUILD(LoopOp, topOfBlock);
    fRXPat->fCompiledPat->addElement(op, *fStatus);

    if ((fIntervalLow & 0xff000000) != 0 ||
        (fIntervalUpper > 0 && (fIntervalUpper & 0xff000000) != 0)) {
            error(U_REGEX_NUMBER_TOO_BIG);
        }

    if (fIntervalLow > fIntervalUpper && fIntervalUpper != -1) {
        error(U_REGEX_MAX_LT_MIN);
    }
}
