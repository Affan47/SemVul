NET_FindLANServer(void)
{
    query_target_t *target;
    query_target_t *responder;

    NET_Query_Init();


    target = GetTargetForAddr(NULL, true);
    target->type = QUERY_TARGET_BROADCAST;


    NET_Query_QueryLoop(NET_Query_ExitCallback, NULL);

    responder = FindFirstResponder();

    if (responder != NULL)
    {
        return responder->addr;
    }
    else
    {
        return NULL;
    }
}
