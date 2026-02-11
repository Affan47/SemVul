globus_l_gfs_ipc_hashtable_session_keyeq(
    void *                              voidp1,
    void *                              voidp2)
{
    globus_l_gfs_ipc_connection_t *     s1;
    globus_l_gfs_ipc_connection_t *     s2;
    GlobusGFSName(globus_l_gfs_ipc_hashtable_session_keyeq);

    s1 = (globus_l_gfs_ipc_connection_t *) voidp1;
    s2 = (globus_l_gfs_ipc_connection_t *) voidp2;


    if(s1->cookie != NULL && s2->cookie != NULL &&
        strcmp(s1->cookie, s2->cookie) == 0)
    {
        return GLOBUS_TRUE;
    }

    globus_assert(s1->host_id && s2->host_id);
    if(strcmp(s1->host_id, s2->host_id) != 0)
    {
        return GLOBUS_FALSE;
    }


    if((s1->username == NULL || s2->username == NULL) &&
        (s1->username != NULL || s2->username != NULL))
    {
        return GLOBUS_FALSE;
    }

    if(s1->username != NULL &&
        strcmp(s1->username, s2->username) != 0)
    {
        return GLOBUS_FALSE;
    }


    if((s1->subject == NULL || s2->subject == NULL) &&
        (s1->subject != NULL || s2->subject != NULL))
    {
        return GLOBUS_FALSE;
    }

    if(s1->subject != NULL &&
        strcmp(s1->subject, s2->subject) != 0)
    {
        return GLOBUS_FALSE;
    }

    return GLOBUS_TRUE;
}
