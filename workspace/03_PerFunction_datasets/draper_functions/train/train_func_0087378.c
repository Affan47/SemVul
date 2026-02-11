agentx_cmd(u_char code)
{
    switch (code) {
    case AGENTX_MSG_OPEN:
        return "Open";
    case AGENTX_MSG_CLOSE:
        return "Close";
    case AGENTX_MSG_REGISTER:
        return "Register";
    case AGENTX_MSG_UNREGISTER:
        return "Unregister";
    case AGENTX_MSG_GET:
        return "Get";
    case AGENTX_MSG_GETNEXT:
        return "Get Next";
    case AGENTX_MSG_GETBULK:
        return "Get Bulk";
    case AGENTX_MSG_TESTSET:
        return "Test Set";
    case AGENTX_MSG_COMMITSET:
        return "Commit Set";
    case AGENTX_MSG_UNDOSET:
        return "Undo Set";
    case AGENTX_MSG_CLEANUPSET:
        return "Cleanup Set";
    case AGENTX_MSG_NOTIFY:
        return "Notify";
    case AGENTX_MSG_PING:
        return "Ping";
    case AGENTX_MSG_INDEX_ALLOCATE:
        return "Index Allocate";
    case AGENTX_MSG_INDEX_DEALLOCATE:
        return "Index Deallocate";
    case AGENTX_MSG_ADD_AGENT_CAPS:
        return "Add Agent Caps";
    case AGENTX_MSG_REMOVE_AGENT_CAPS:
        return "Remove Agent Caps";
    case AGENTX_MSG_RESPONSE:
        return "Response";
    default:
        return "Unknown";
    }
}
