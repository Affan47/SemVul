CK_RVtoStr(CK_RV errNum) {
    CK_ULONG low  = 1;
    CK_ULONG high = numStrings - 1;
    CK_ULONG i;
    CK_RV num;
    static int initDone;


    if (!initDone) {
        CK_RV lastNum = CKR_OK;
        for (i = low; i <= high; ++i) {
            num = errStrings[i].errNum;
            if (num <= lastNum) {
                PR_fprintf(PR_STDERR,
                        "sequence error in error strings at item %d\n"
                        "error %d (%s)\n"
                        "should come after \n"
                        "error %d (%s)\n",
                        (int) i, (int) lastNum, errStrings[i-1].errString,
                        (int) num, errStrings[i].errString);
            }
            lastNum = num;
        }
        initDone = 1;
    }


    while (low + 1 < high) {
        i = (low + high) / 2;
        num = errStrings[i].errNum;
        if (errNum == num)
            return errStrings[i].errString;
        if (errNum < num)
            high = i;
        else
            low = i;
    }
    if (errNum == errStrings[low].errNum)
        return errStrings[low].errString;
    if (errNum == errStrings[high].errNum)
        return errStrings[high].errString;
    return "unknown error";
}
