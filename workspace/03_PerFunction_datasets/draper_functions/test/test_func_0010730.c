isFloatValue(float& fvalue, int& charsize)
{

    bool valuefound = false;

    const char* startptr = mSource + mCharPos;
    char* endptr = NULL;

    fvalue = (float)strtod(startptr, &endptr);

    if(endptr) {
        if(endptr>startptr) {

            charsize = endptr - startptr;
            valuefound = true;
        }
    }

    return valuefound;
}
