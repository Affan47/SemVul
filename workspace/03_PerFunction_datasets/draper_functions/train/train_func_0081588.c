getHost(void *data)
{
    service *svc = getService(data);
    if (svc)
        return svc->host_ptr;
    else
        return 0;
}
