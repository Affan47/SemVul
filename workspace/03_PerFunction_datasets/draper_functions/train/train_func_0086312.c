ExHostToFQDN( const char host[], char fqdn[MAXHOSTNAMELEN] )
{
    long addr;
    struct hostent *hp, *hp2;

    hp = gethostbyname(host);
    if ( hp == NULL || hp->h_addr_list[0] == NULL ) {
       DXUIMessage("WARNING", "gethostbyname returned error");
       DXUIMessage("WARNING", "it appears %s doesn't have a host entry?", host);
       DXUIMessage("WARNING", "trying localhost.");
       addr = 0x7f000001;
    } else
    	addr = *(long *)hp->h_addr_list[0];

    hp2 = gethostbyaddr((const char *)&addr, sizeof(struct in_addr),
                        AF_INET );
    if ( hp2 == NULL || hp2->h_name == NULL ) {
        if(_dxfHostIsLocal((char *)host)) {
            strncpy( fqdn, "localhost", MAXHOSTNAMELEN );
            DXMessage("Warning: Cannot get FQDN; no DNS entry. Assuming localhost.");
            return OK;
        }
        DXUIMessage("ERROR", "gethostbyaddr returned error");
        DXSetError(ERROR_UNEXPECTED, "gethostbyaddr error--is it possible this machine doesn't have a DNS/host entry?");
        return ERROR;
    }
    strncpy( fqdn, hp2->h_name, MAXHOSTNAMELEN );
    return OK;
}
