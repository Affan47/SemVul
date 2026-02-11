putCharInBuffer(char charToAdd)
{

    if (xmlPrettyPrintedIndex >= xmlPrettyPrintedLength)
    {
        char* reallocated;

        if (charToAdd == '\0') { ++xmlPrettyPrintedLength; }
        else { xmlPrettyPrintedLength += inputBufferLength; }
        reallocated = (char*)realloc(xmlPrettyPrinted, xmlPrettyPrintedLength);
        if (reallocated == NULL) { PP_ERROR("Allocation error (char was %c)", charToAdd); return; }
        xmlPrettyPrinted = reallocated;
    }


    xmlPrettyPrinted[xmlPrettyPrintedIndex] = charToAdd;
    ++xmlPrettyPrintedIndex;
}
