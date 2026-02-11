SetupUnikeyEngine()
{
    SetupInputClassifierTable();
    int i;
    VnLexiName lexi;


    for (i=0; i < 256; i++) {
        IsoStdVnCharMap[i] = i;
    }

    for (i=0; SpecialWesternChars[i]; i++) {
        IsoStdVnCharMap[SpecialWesternChars[i]] = (vnl_lastChar + i) + VnStdCharOffset;
    }

    for (i=0; i < 256; i++) {
        if ((lexi = IsoToVnLexi(i)) != vnl_nonVnChar) {
            IsoStdVnCharMap[i] = lexi + VnStdCharOffset;
        }
    }
}
