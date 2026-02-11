globus_l_gram_get_job_contact_from_uri(
    const char *                        uri)
{
    int                                 n;
    int                                 rc;
    if (uri[0] == '/')
    {
        return uri;
    }
    else
    {
        rc = sscanf(uri, "https://%*[^:]%*[:0-9]%n", &n);
        if (rc < 0)
        {
            return NULL;
        }
        return uri+n;
    }
}
