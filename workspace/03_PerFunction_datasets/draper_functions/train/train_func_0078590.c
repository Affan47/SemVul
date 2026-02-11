GetNumResponses(void)
{
    unsigned int i;
    int result;

    result = 0;

    for (i = 0; i < num_targets; ++i)
    {
        if (targets[i].type == QUERY_TARGET_SERVER
         && targets[i].state == QUERY_TARGET_RESPONDED)
        {
            ++result;
        }
    }

    return result;
}
