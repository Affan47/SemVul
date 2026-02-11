node_blacklisted(const struct sockaddr *sa, int salen)
{
    int i;

    if((unsigned)salen > sizeof(struct sockaddr_storage))
        abort();

    if(dht_blacklisted(sa, salen))
        return 1;

    for(i = 0; i < DHT_MAX_BLACKLISTED; i++) {
        if(memcmp(&blacklist[i], sa, salen) == 0)
            return 1;
    }

    return 0;
}
