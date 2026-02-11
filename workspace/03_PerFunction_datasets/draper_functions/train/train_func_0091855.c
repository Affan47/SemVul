getapp(host, login, app_name, p_q)
char *host;
char *login;
char *app_name;
cid_getapp_ot *p_q;
{
        cid_getapp_ot in;
	char appname[NAME_LEN];
	int	k;
        int cidsock;
        u_short op ;

        if ((cidsock = connectCid(host,login)) == -1)
        {
                printf(" Cannot reach CID \n");
		close(cidsock);
                return 0;
        }
        op = htons(CID_OP_GET_APP);
	strcpy(appname,app_name);
        if (writen(cidsock, (char *)&op, sizeof(u_short)))
        {
        	if (!writen(cidsock, appname, sizeof(appname))) {
                	printf("Error : CIDLIB GetApp_Writen_Appnm\n");
			close(cidsock);
			return 0;
		}
        	if (!readn(cidsock, (char *)&in, sizeof(cid_getapp_ot))) {
                	printf("Error : CIDLIB GetApp_Readn_In\n");
                	close(cidsock);
			return 0;
        	}
		*p_q = in;
        } else {
                printf("Error : CIDLIB GetApp_Send_Op\n");
                close(cidsock);
                return 0;
        }
        close(cidsock);
        return 1;
}
