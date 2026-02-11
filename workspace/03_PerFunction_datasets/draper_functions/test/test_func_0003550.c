glusterd_remote_hostname_get (rpcsvc_request_t *req, char *remote_host, int len)
{
        GF_ASSERT (req);
        GF_ASSERT (remote_host);
        GF_ASSERT (req->trans);

        char *name = NULL;
        char *hostname = NULL;
        char *tmp_host = NULL;
        int  ret = 0;

        name = req->trans->peerinfo.identifier;
        tmp_host = gf_strdup (name);
        if (tmp_host)
                get_host_name (tmp_host, &hostname);

        GF_ASSERT (hostname);
        if (!hostname) {
                memset (remote_host, 0, len);
                ret = -1;
                goto out;
        }

        strncpy (remote_host, hostname, strlen (hostname));


out:
        GF_FREE (tmp_host);
        return ret;
}
