http_url_path(const char *url)
{
    const char *s;

    s = http_strip_resource_type(url);
    s = strchr(s, '/');
    if(s == NULL)
        return av_strdup("/");
    else
        return av_strdup(s);
}
