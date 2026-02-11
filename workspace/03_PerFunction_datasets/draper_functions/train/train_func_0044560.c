FAMMonitor(FAMConnection *fc, const char *filename, FAMRequest* fr,
	       void* userData, int code)
{

    if (!filename || filename[0] != '/')
	return -1;

    int reqnum = fr->reqnum;
    Client *client = (Client *)fc->client;

    if(userData != NULL) client->storeUserData(reqnum, userData);

    GroupStuff groups;
    char msg[MSGBUFSIZ];
    int msgLen;
    snprintf(msg, MSGBUFSIZ, "%c%d %d %d %s\n", code, reqnum, geteuid(),
                             groups.groups[0], filename);
    msgLen = strlen(msg) + 1;
    if(groups.ngroups > 1)
    {
        msgLen += groups.groupString(msg + msgLen, MSGBUFSIZ - msgLen);
        ++msgLen;
    }


    client->writeToServer(msg, msgLen);
    return(0);
}
