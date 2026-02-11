process_rvn_packet(struct rvn *rvnpacket)
{
    int ccfd;
    extern int h_errno;
    struct sockaddr_un ccsa;

    struct hostent *he;

    ccfd = socket(PF_UNIX, SOCK_DGRAM, 0);

    he = gethostbyaddr((char *) &(rvnpacket->saddr),
                       sizeof(struct in_addr), AF_INET);

    if (he == NULL)
        strcpy(rvnpacket->fqdn, inet_ntoa(rvnpacket->saddr));
    else {
        bzero(rvnpacket->fqdn, 45);
        strncpy(rvnpacket->fqdn, he->h_name, 44);
    }

    ccsa.sun_family = AF_UNIX;
    strcpy(ccsa.sun_path, CHILDSOCKNAME);

    sendto(ccfd, rvnpacket, sizeof(struct rvn), 0,
           (struct sockaddr *) &ccsa,
           sizeof(ccsa.sun_family) + strlen(ccsa.sun_path));
    close(ccfd);
}
