LASIpTreeDealloc(LASIpTree_t *startnode)
{
    int    i;

    if (startnode == NULL)
        return;


    if (LAS_IP_IS_CONSTANT(startnode))
        return;


    for (i=0; i<2; i++) {
        if (!(LAS_IP_IS_CONSTANT(startnode->action[i])))
            LASIpTreeDealloc(startnode->action[i]);
    }


    PERM_FREE(startnode);
}
