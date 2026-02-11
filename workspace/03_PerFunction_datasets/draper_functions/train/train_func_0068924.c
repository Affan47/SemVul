findCandidates(Parameter parameters[], void (*instanceMatcher)(Parameter *parameter))
{
    int i;

    for (i = 0; i < lengthOfParameterArray(parameters); i++) {
        parameters[i].candidates = ensureParameterArrayAllocated(parameters[i].candidates);
        instanceMatcher(&parameters[i]);
        parameters[i].candidates[0].isPronoun = parameters[i].isPronoun;
    }
}
