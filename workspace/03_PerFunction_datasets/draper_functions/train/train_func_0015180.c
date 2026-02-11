doCodepageCreate(const char *codepageData,
                                int32_t dataLength,
                                UConverter *converter,
                                UErrorCode &status)
{
    if(U_FAILURE(status)) {
        return;
    }


    const char *mySource     = codepageData;
    const char *mySourceEnd  = mySource + dataLength;
    UChar *array, *myTarget;


    int32_t arraySize;
    if(dataLength <= US_STACKBUF_SIZE) {

        arraySize = US_STACKBUF_SIZE;
    } else {

        arraySize = dataLength + (dataLength >> 2);
    }


    UBool doCopyArray = FALSE;
    for(;;) {
        if(!cloneArrayIfNeeded(arraySize, arraySize, doCopyArray)) {
            setToBogus();
            break;
        }


        array = getArrayStart();
        myTarget = array + length();
        ucnv_toUnicode(converter, &myTarget,  array + getCapacity(),
            &mySource, mySourceEnd, 0, TRUE, &status);


        setLength((int32_t)(myTarget - array));


        if(status == U_BUFFER_OVERFLOW_ERROR) {

            status = U_ZERO_ERROR;


            doCopyArray = TRUE;


            arraySize = (int32_t)(length() + 2 * (mySourceEnd - mySource));
        } else {
            break;
        }
    }
}
