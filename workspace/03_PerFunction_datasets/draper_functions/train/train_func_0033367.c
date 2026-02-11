blockTopLoc(UBool reserveLoc) {
    int32_t   theLoc;
    fixLiterals(TRUE);

    if (fRXPat->fCompiledPat->size() == fMatchCloseParen)
    {

        theLoc = fMatchOpenParen;
        U_ASSERT(theLoc > 0);
        U_ASSERT(URX_TYPE(((uint32_t)fRXPat->fCompiledPat->elementAti(theLoc))) == URX_NOP);
    }
    else {


        theLoc = fRXPat->fCompiledPat->size()-1;
        int32_t opAtTheLoc = (int32_t)fRXPat->fCompiledPat->elementAti(theLoc);
        if (URX_TYPE(opAtTheLoc) == URX_STRING_LEN) {


            theLoc--;
        }
        if (reserveLoc) {
            int32_t  nop = URX_BUILD(URX_NOP, 0);
            fRXPat->fCompiledPat->insertElementAt(nop, theLoc, *fStatus);
        }
    }
    return theLoc;
}
