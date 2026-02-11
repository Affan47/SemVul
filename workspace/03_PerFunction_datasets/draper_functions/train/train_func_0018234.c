compileSet(UnicodeSet *theSet)
{
    if (theSet == NULL) {
        return;
    }


    theSet->removeAllStrings();
    int32_t  setSize = theSet->size();
    UChar32  firstSetChar = theSet->charAt(0);

    switch (setSize) {
    case 0:
        {

            fRXPat->fCompiledPat->addElement(URX_BUILD(URX_BACKTRACK, 0), *fStatus);
            delete theSet;
        }
        break;

    case 1:
        {


            literalChar(firstSetChar);
            delete theSet;
        }
        break;

    default:
        {


            int32_t setNumber = fRXPat->fSets->size();
            fRXPat->fSets->addElement(theSet, *fStatus);
            int32_t setOp = URX_BUILD(URX_SETREF, setNumber);
            fRXPat->fCompiledPat->addElement(setOp, *fStatus);
        }
    }
}
