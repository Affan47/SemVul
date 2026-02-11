glusterd_is_local_addr (char *hostname)
{
        int32_t         ret = -1;
        struct          addrinfo *result = NULL;
        struct          addrinfo *res = NULL;
        gf_boolean_t    found = _gf_false;
        char            *ip = NULL;
        xlator_t        *this = NULL;

        this = THIS;
        ret = getaddrinfo (hostname, NULL, NULL, &result);

        if (ret != 0) {
                gf_log (this->name, GF_LOG_ERROR, "error in getaddrinfo: %s\n",
                        gai_strerror(ret));
                goto out;
        }

        for (res = result; res != NULL; res = res->ai_next) {
                gf_log (this->name, GF_LOG_DEBUG, "%s ",
                        get_ip_from_addrinfo (res, &ip));

                found = glusterd_is_loopback_localhost (res->ai_addr, hostname)
                        || glusterd_interface_search (ip);
                if (found) {
                        GF_FREE (ip);
                        goto out;
                }
                GF_FREE (ip);
        }

out:
        if (result)
                freeaddrinfo (result);

        if (!found)
                gf_log (this->name, GF_LOG_DEBUG, "%s is not local", hostname);

        return found;
}
