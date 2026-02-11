http_set_client_timeout(long timeout)
{
    http_client_timeout = timeout;
    if (client_fdset != NULL) {

        fdset_set_timeout(client_fdset, http_client_timeout);
    }
}
