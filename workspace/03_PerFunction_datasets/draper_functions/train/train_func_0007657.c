setCalculationType(ECalculationType type, UErrorCode &status)
{
    if (cType != type) {


        UDate m = getTimeInMillis(status);
        cType = type;
        clear();
        setTimeInMillis(m, status);
    }
}
