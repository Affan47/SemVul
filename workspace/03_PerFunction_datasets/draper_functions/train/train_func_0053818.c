getHostname (bool fqdn)
{
    char const * hostname = "unknown";
    int ret;
    OFVector<char> hn (1024, 0);

    while (true)
    {
        ret = ::gethostname (&hn[0], OFstatic_cast(int, hn.size ()) - 1);
        if (ret == 0)
        {
            hostname = &hn[0];
            break;
        }
#if defined (DCMTK_LOG4CPLUS_HAVE_ENAMETOOLONG)
        else if (ret != 0 && errno == ENAMETOOLONG)

            hn.resize (hn.size () * 2, 0);
#endif
        else
            break;
    }

    if (ret != 0 || (ret == 0 && ! fqdn))
        return DCMTK_LOG4CPLUS_STRING_TO_TSTRING (hostname);

    STD_NAMESPACE string full_hostname;
    ret = get_host_by_name (hostname, &full_hostname, 0);
    if (ret == 0)
        hostname = full_hostname.c_str ();

    return DCMTK_LOG4CPLUS_STRING_TO_TSTRING (hostname);
}
