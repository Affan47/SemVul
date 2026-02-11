fsa_state2string(enum crmd_fsa_state state)
{
    const char *stateAsText = NULL;

    switch (state) {
        case S_IDLE:
            stateAsText = "S_IDLE";
            break;
        case S_ELECTION:
            stateAsText = "S_ELECTION";
            break;
        case S_INTEGRATION:
            stateAsText = "S_INTEGRATION";
            break;
        case S_FINALIZE_JOIN:
            stateAsText = "S_FINALIZE_JOIN";
            break;
        case S_NOT_DC:
            stateAsText = "S_NOT_DC";
            break;
        case S_POLICY_ENGINE:
            stateAsText = "S_POLICY_ENGINE";
            break;
        case S_RECOVERY:
            stateAsText = "S_RECOVERY";
            break;
        case S_RELEASE_DC:
            stateAsText = "S_RELEASE_DC";
            break;
        case S_PENDING:
            stateAsText = "S_PENDING";
            break;
        case S_STOPPING:
            stateAsText = "S_STOPPING";
            break;
        case S_TERMINATE:
            stateAsText = "S_TERMINATE";
            break;
        case S_TRANSITION_ENGINE:
            stateAsText = "S_TRANSITION_ENGINE";
            break;
        case S_STARTING:
            stateAsText = "S_STARTING";
            break;
        case S_HALT:
            stateAsText = "S_HALT";
            break;
        case S_ILLEGAL:
            stateAsText = "S_ILLEGAL";
            break;
    }

    if (stateAsText == NULL) {
        crm_err("State %d is unknown", state);
        stateAsText = "<UNKNOWN_STATE>";
    }

    return stateAsText;
}
