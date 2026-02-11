fsa_input2string(enum crmd_fsa_input input)
{
    const char *inputAsText = NULL;

    switch (input) {
        case I_NULL:
            inputAsText = "I_NULL";
            break;
        case I_CIB_OP:
            inputAsText = "I_CIB_OP (unused)";
            break;
        case I_CIB_UPDATE:
            inputAsText = "I_CIB_UPDATE";
            break;
        case I_DC_TIMEOUT:
            inputAsText = "I_DC_TIMEOUT";
            break;
        case I_ELECTION:
            inputAsText = "I_ELECTION";
            break;
        case I_PE_CALC:
            inputAsText = "I_PE_CALC";
            break;
        case I_RELEASE_DC:
            inputAsText = "I_RELEASE_DC";
            break;
        case I_ELECTION_DC:
            inputAsText = "I_ELECTION_DC";
            break;
        case I_ERROR:
            inputAsText = "I_ERROR";
            break;
        case I_FAIL:
            inputAsText = "I_FAIL";
            break;
        case I_INTEGRATED:
            inputAsText = "I_INTEGRATED";
            break;
        case I_FINALIZED:
            inputAsText = "I_FINALIZED";
            break;
        case I_NODE_JOIN:
            inputAsText = "I_NODE_JOIN";
            break;
        case I_JOIN_OFFER:
            inputAsText = "I_JOIN_OFFER";
            break;
        case I_JOIN_REQUEST:
            inputAsText = "I_JOIN_REQUEST";
            break;
        case I_JOIN_RESULT:
            inputAsText = "I_JOIN_RESULT";
            break;
        case I_NOT_DC:
            inputAsText = "I_NOT_DC";
            break;
        case I_RECOVERED:
            inputAsText = "I_RECOVERED";
            break;
        case I_RELEASE_FAIL:
            inputAsText = "I_RELEASE_FAIL";
            break;
        case I_RELEASE_SUCCESS:
            inputAsText = "I_RELEASE_SUCCESS";
            break;
        case I_RESTART:
            inputAsText = "I_RESTART";
            break;
        case I_PE_SUCCESS:
            inputAsText = "I_PE_SUCCESS";
            break;
        case I_ROUTER:
            inputAsText = "I_ROUTER";
            break;
        case I_SHUTDOWN:
            inputAsText = "I_SHUTDOWN";
            break;
        case I_STARTUP:
            inputAsText = "I_STARTUP";
            break;
        case I_TE_SUCCESS:
            inputAsText = "I_TE_SUCCESS";
            break;
        case I_STOP:
            inputAsText = "I_STOP";
            break;
        case I_DC_HEARTBEAT:
            inputAsText = "I_DC_HEARTBEAT";
            break;
        case I_WAIT_FOR_EVENT:
            inputAsText = "I_WAIT_FOR_EVENT";
            break;
        case I_LRM_EVENT:
            inputAsText = "I_LRM_EVENT";
            break;
        case I_PENDING:
            inputAsText = "I_PENDING";
            break;
        case I_HALT:
            inputAsText = "I_HALT";
            break;
        case I_TERMINATE:
            inputAsText = "I_TERMINATE";
            break;
        case I_ILLEGAL:
            inputAsText = "I_ILLEGAL";
            break;
    }

    if (inputAsText == NULL) {
        crm_err("Input %d is unknown", input);
        inputAsText = "<UNKNOWN_INPUT>";
    }

    return inputAsText;
}
