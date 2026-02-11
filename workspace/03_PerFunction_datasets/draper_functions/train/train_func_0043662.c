ucm_addState(UCMStates *states, const char *s) {
    const char *error;

    if(states->countStates==MBCS_MAX_STATE_COUNT) {
        fprintf(stderr, "ucm error: too many states (maximum %u)\n", MBCS_MAX_STATE_COUNT);
        exit(U_INVALID_TABLE_FORMAT);
    }

    error=parseState(s, states->stateTable[states->countStates],
                       &states->stateFlags[states->countStates]);
    if(error!=NULL) {
        fprintf(stderr, "ucm error: parse error in state definition at '%s'\n", error);
        exit(U_INVALID_TABLE_FORMAT);
    }

    ++states->countStates;
}
