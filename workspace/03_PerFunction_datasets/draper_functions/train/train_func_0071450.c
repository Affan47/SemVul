subtractParameterArrays(Parameter theArray[], Parameter remove[])
{
    int i;

    if (remove == NULL) return;

    for (i = 0; !isEndOfArray(&theArray[i]); i++)
        if (inParameterArray(remove, theArray[i].instance))
            theArray[i].instance = 0;
    compressParameterArray(theArray);
}
