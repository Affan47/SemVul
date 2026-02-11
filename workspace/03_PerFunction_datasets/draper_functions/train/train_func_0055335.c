setParameters(Parameter *newParameters) {
    if (globalParameters == NULL)
        globalParameters = allocateParameterArray(MAXENTITY);
    copyParameterArray(globalParameters, newParameters);
}
