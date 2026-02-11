name_resolved(struct rvn *rvnpacket, struct hosts *hostlist,
                  unsigned int lastfree)
{
    unsigned int i = 0;

    while (i != lastfree) {
        if ((rvnpacket->saddr.s_addr == hostlist[i].addr)
            && (hostlist[i].ready == RESOLVED))
            return i;

        i++;
    }

    return -1;
}
