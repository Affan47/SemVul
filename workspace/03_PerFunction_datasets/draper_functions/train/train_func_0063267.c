parseReference(Parameter parameters[]) {
    clearParameterArray(parameters);

    if (isLiteralWord(currentWordIndex)) {
        parseLiteral(parameters);
    } else if (isPronounWord(currentWordIndex)) {
        parsePronoun(parameters);
    } else {
        parseAdjectivesAndNoun(parameters);
    }
}
