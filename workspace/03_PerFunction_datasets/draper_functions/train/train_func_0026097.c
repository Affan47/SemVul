errorNoSuch(Parameter parameter) {


    if (parameter.instance == -1)
        parameter.instance = 0;
    if (parameter.instance == 0)
        parameter.instance = findInstanceForNoun(playerWords[parameter.lastWord].code);
    parameter.useWords = TRUE;

    addParameter(&globalParameters[0], &parameter);
    error(M_NO_SUCH);
}
