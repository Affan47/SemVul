stripCharsFromStringBackwards(Aint count, char *initialString, char **theRest) {
    int stripPosition;
    char *strippedString;
    char *rest;

    if (count > strlen(initialString))
        stripPosition = 0;
    else
        stripPosition = strlen(initialString)-count;
    strippedString = strdup(&initialString[stripPosition]);
    rest = strdup(initialString);
    rest[stripPosition] = '\0';
    *theRest = rest;
    return strippedString;
}
