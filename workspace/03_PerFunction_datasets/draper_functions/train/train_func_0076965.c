countTrailingBlanks(char *string, int position) {
    int skippedChars, i;
    skippedChars = 0;

    if (position > strlen(string)-1)
        syserr("position > length in countTrailingBlanks");
    for (i = position; i >= 0 && string[i] == ' '; i--)
        skippedChars++;
    return(skippedChars);
}
